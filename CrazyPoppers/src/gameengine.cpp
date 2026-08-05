#include "gameengine.h"

#include "leveldata.h"

#include <QSettings>

#include <utility>

namespace {

constexpr qreal kBulletSpeed = 9.0;  // cells per second
constexpr int kTickInterval = 16;    // ms
constexpr qreal kMaxStep = 0.45;     // cells per tick — below 0.5 so a bullet can never
                                     // skip past a cell centre between two collision checks
constexpr int kPopScore = 50;        // multiplied by the running combo
constexpr int kClearBonus = 250;     // per unused tap when the board is cleared
constexpr int kMaxTier = 4;          // red

QString scoreKey(int levelIndex)
{
    return QStringLiteral("scores/level%1").arg(levelIndex);
}

const QString kUnlockedKey = QStringLiteral("progress/highestUnlockedLevel");

} // namespace

GameEngine::GameEngine(QObject *parent)
    : QObject(parent)
{
    m_ticker.setInterval(kTickInterval);
    m_ticker.setTimerType(Qt::PreciseTimer);
    connect(&m_ticker, &QTimer::timeout, this, &GameEngine::advance);

    loadProgress();
    startLevel(0);
}

int GameEngine::levelCount() const
{
    return int(levelLibrary().size());
}

QString GameEngine::levelName() const
{
    return levelNameAt(m_levelIndex);
}

QString GameEngine::levelNameAt(int index) const
{
    const auto &library = levelLibrary();
    if (index < 0 || index >= library.size())
        return {};
    return library.at(index).name;
}

int GameEngine::tapBudgetAt(int index) const
{
    const auto &library = levelLibrary();
    if (index < 0 || index >= library.size())
        return 0;
    return library.at(index).taps;
}

void GameEngine::startLevel(int index)
{
    const auto &library = levelLibrary();
    if (library.isEmpty())
        return;

    m_levelIndex = qBound(0, index, int(library.size()) - 1);
    const LevelDefinition &level = library.at(m_levelIndex);

    m_ticker.stop();
    m_bullets.clear();
    m_board.load(level);

    m_tapBudget = level.taps;
    m_tapsRemaining = level.taps;
    m_tapsUsed = 0;
    m_score = 0;
    m_combo = 0;

    const bool wasPaused = std::exchange(m_paused, false);
    setPhase(Idle);

    emit levelChanged();
    emit tapsChanged();
    emit scoreChanged();
    emit comboChanged();
    if (wasPaused)
        emit pausedChanged();
}

void GameEngine::restartLevel()
{
    startLevel(m_levelIndex);
}

void GameEngine::nextLevel()
{
    if (m_levelIndex + 1 < levelCount())
        startLevel(m_levelIndex + 1);
}

void GameEngine::tap(int row, int column)
{
    if (m_phase != Idle || m_paused || !m_board.contains(row, column))
        return;

    // Tapping bare ground is a miss, not a wasted tap.
    if (m_board.tierAt(m_board.indexOf(row, column)) == 0)
        return;

    --m_tapsRemaining;
    ++m_tapsUsed;
    emit tapsChanged();

    m_combo = 0;
    emit comboChanged();

    hitCell(row, column);

    if (m_bullets.count() > 0) {
        setPhase(Resolving);
        m_clock.start();
        m_ticker.start();
    } else {
        settle();
    }
}

int GameEngine::bestScore(int levelIndex) const
{
    QSettings settings;
    return settings.value(scoreKey(levelIndex), 0).toInt();
}

void GameEngine::setPaused(bool paused)
{
    if (m_paused == paused)
        return;

    m_paused = paused;
    if (m_paused) {
        m_ticker.stop();
    } else if (m_phase == Resolving) {
        m_clock.restart();
        m_ticker.start();
    }
    emit pausedChanged();
}

void GameEngine::advance()
{
    const qreal step = qMin(kMaxStep, kBulletSpeed * qreal(m_clock.restart()) / 1000.0);

    // Walking backwards makes removal cheap, and leaves bullets spawned by this
    // frame's collisions sitting at index >= count() so they only start moving
    // next frame. That one-frame delay is what makes a cascade read as a
    // sequence of pops rather than a single flash.
    for (int i = m_bullets.count() - 1; i >= 0; --i) {
        Bullet &bullet = m_bullets.bulletAt(i);
        bullet.x += bullet.directionX * step;
        bullet.y += bullet.directionY * step;

        const int row = qRound(bullet.y);
        const int column = qRound(bullet.x);
        if (row == bullet.lastRow && column == bullet.lastColumn)
            continue;

        if (!m_board.contains(row, column)) {
            m_bullets.removeAt(i);
            continue;
        }

        bullet.lastRow = row;
        bullet.lastColumn = column;

        if (m_board.tierAt(m_board.indexOf(row, column)) > 0) {
            m_bullets.removeAt(i);
            hitCell(row, column);
        }
    }

    m_bullets.notifyPositions();

    if (m_bullets.count() == 0) {
        m_ticker.stop();
        settle();
    }
}

void GameEngine::hitCell(int row, int column)
{
    const int index = m_board.indexOf(row, column);
    const int tier = m_board.tierAt(index);
    if (tier == 0)
        return;

    if (tier < kMaxTier) {
        m_board.setTierAt(index, tier + 1);
        return;
    }

    m_board.setTierAt(index, 0);

    ++m_combo;
    emit comboChanged();

    m_score += kPopScore * m_combo;
    emit scoreChanged();

    m_bullets.spawnBurst(row, column);
    emit popped(row, column, tier);
}

void GameEngine::settle()
{
    if (m_board.creatureCount() == 0) {
        m_score += m_tapsRemaining * kClearBonus;
        emit scoreChanged();
        recordResult();
        setPhase(Won);
    } else if (m_tapsRemaining <= 0) {
        setPhase(Lost);
    } else {
        setPhase(Idle);
    }
}

void GameEngine::setPhase(Phase phase)
{
    if (m_phase == phase)
        return;

    m_phase = phase;
    emit phaseChanged();
}

void GameEngine::loadProgress()
{
    QSettings settings;
    m_highestUnlockedLevel = qBound(0, settings.value(kUnlockedKey, 0).toInt(),
                                    qMax(0, levelCount() - 1));
}

void GameEngine::recordResult()
{
    QSettings settings;

    const QString key = scoreKey(m_levelIndex);
    if (m_score > settings.value(key, 0).toInt())
        settings.setValue(key, m_score);

    const int unlocked = m_levelIndex + 1;
    if (unlocked > m_highestUnlockedLevel && unlocked < levelCount()) {
        m_highestUnlockedLevel = unlocked;
        settings.setValue(kUnlockedKey, m_highestUnlockedLevel);
        emit highestUnlockedLevelChanged();
    }
}
