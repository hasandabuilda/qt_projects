#pragma once

#include <QAbstractListModel>
#include <QtQmlIntegration/qqmlintegration.h>

/*!
    One projectile emitted by a popped creature.

    Position is expressed in continuous grid coordinates: whole numbers sit on
    cell centres, so the view only has to multiply by the cell size. \c lastRow
    and \c lastColumn remember which cell the bullet was last counted as being
    inside, which is how the engine detects a crossing into a new cell.
*/
struct Bullet
{
    qreal x = 0.0;
    qreal y = 0.0;
    int directionX = 0;
    int directionY = 0;
    int lastRow = 0;
    int lastColumn = 0;
};

/*!
    Live projectiles, in flight order.

    The model is deliberately passive: GameEngine owns the simulation and
    mutates bullets through \l bulletAt(), then calls \l notifyPositions() once
    per frame so the whole flight is a single change signal rather than one per
    projectile.
*/
class BulletModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Role {
        XRole = Qt::UserRole + 1,
        YRole,
        DirectionXRole,
        DirectionYRole,
    };

    explicit BulletModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const { return int(m_bullets.size()); }

    void clear();
    void spawnBurst(int row, int column);
    void removeAt(int index);
    void notifyPositions();

    Bullet &bulletAt(int index) { return m_bullets[index]; }
    const Bullet &bulletAt(int index) const { return m_bullets.at(index); }

signals:
    void countChanged();

private:
    QList<Bullet> m_bullets;
};
