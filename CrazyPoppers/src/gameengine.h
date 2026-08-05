#pragma once

#include <QElapsedTimer>
#include <QObject>
#include <QTimer>
#include <QtQmlIntegration/qqmlintegration.h>

#include "boardmodel.h"
#include "bulletmodel.h"

/*!
    Rules and simulation for a single run at a level.

    A tap either ripens a creature one tier or, if it was already red, pops it
    into four bullets. Bullets fly outwards at a constant speed and hit the
    first creature they meet, which reacts exactly as if it had been tapped, so
    one tap can cascade across the whole board. Input is refused while a
    cascade is still resolving, and the level is judged only once the board has
    gone quiet again.
*/
class GameEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(BoardModel *board READ board CONSTANT)
    Q_PROPERTY(BulletModel *bullets READ bullets CONSTANT)
    Q_PROPERTY(Phase phase READ phase NOTIFY phaseChanged)
    Q_PROPERTY(int levelIndex READ levelIndex NOTIFY levelChanged)
    Q_PROPERTY(int levelCount READ levelCount CONSTANT)
    Q_PROPERTY(QString levelName READ levelName NOTIFY levelChanged)
    Q_PROPERTY(int tapBudget READ tapBudget NOTIFY levelChanged)
    Q_PROPERTY(int tapsRemaining READ tapsRemaining NOTIFY tapsChanged)
    Q_PROPERTY(int tapsUsed READ tapsUsed NOTIFY tapsChanged)
    Q_PROPERTY(int score READ score NOTIFY scoreChanged)
    Q_PROPERTY(int combo READ combo NOTIFY comboChanged)
    Q_PROPERTY(bool paused READ isPaused WRITE setPaused NOTIFY pausedChanged)
    Q_PROPERTY(int highestUnlockedLevel READ highestUnlockedLevel NOTIFY highestUnlockedLevelChanged)

public:
    enum Phase {
        Idle,      //!< Waiting for the player.
        Resolving, //!< Bullets in flight; input is locked.
        Won,
        Lost,
    };
    Q_ENUM(Phase)

    explicit GameEngine(QObject *parent = nullptr);

    BoardModel *board() { return &m_board; }
    BulletModel *bullets() { return &m_bullets; }

    Phase phase() const { return m_phase; }
    int levelIndex() const { return m_levelIndex; }
    int levelCount() const;
    QString levelName() const;
    int tapBudget() const { return m_tapBudget; }
    int tapsRemaining() const { return m_tapsRemaining; }
    int tapsUsed() const { return m_tapsUsed; }
    int score() const { return m_score; }
    int combo() const { return m_combo; }
    bool isPaused() const { return m_paused; }
    void setPaused(bool paused);
    int highestUnlockedLevel() const { return m_highestUnlockedLevel; }

    Q_INVOKABLE void startLevel(int index);
    Q_INVOKABLE void restartLevel();
    Q_INVOKABLE void nextLevel();
    Q_INVOKABLE void tap(int row, int column);
    Q_INVOKABLE int bestScore(int levelIndex) const;
    Q_INVOKABLE QString levelNameAt(int index) const;
    Q_INVOKABLE int tapBudgetAt(int index) const;

signals:
    void phaseChanged();
    void levelChanged();
    void tapsChanged();
    void scoreChanged();
    void comboChanged();
    void pausedChanged();
    void highestUnlockedLevelChanged();

    //! A creature burst at this cell — the view answers with a shockwave.
    void popped(int row, int column, int tier);

private:
    void advance();
    void hitCell(int row, int column);
    void settle();
    void setPhase(Phase phase);
    void loadProgress();
    void recordResult();

    BoardModel m_board;
    BulletModel m_bullets;
    QTimer m_ticker;
    QElapsedTimer m_clock;

    Phase m_phase = Idle;
    int m_levelIndex = 0;
    int m_tapBudget = 0;
    int m_tapsRemaining = 0;
    int m_tapsUsed = 0;
    int m_score = 0;
    int m_combo = 0;
    bool m_paused = false;
    int m_highestUnlockedLevel = 0;
};
