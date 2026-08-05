#include "bulletmodel.h"

BulletModel::BulletModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int BulletModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : int(m_bullets.size());
}

QVariant BulletModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_bullets.size())
        return {};

    const Bullet &bullet = m_bullets.at(index.row());
    switch (role) {
    case XRole:
        return bullet.x;
    case YRole:
        return bullet.y;
    case DirectionXRole:
        return bullet.directionX;
    case DirectionYRole:
        return bullet.directionY;
    default:
        return {};
    }
}

QHash<int, QByteArray> BulletModel::roleNames() const
{
    return {
        { XRole, "gridX" },
        { YRole, "gridY" },
        { DirectionXRole, "directionX" },
        { DirectionYRole, "directionY" },
    };
}

void BulletModel::clear()
{
    if (m_bullets.isEmpty())
        return;

    beginResetModel();
    m_bullets.clear();
    endResetModel();
    emit countChanged();
}

void BulletModel::spawnBurst(int row, int column)
{
    static constexpr int directions[4][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

    const int first = int(m_bullets.size());
    beginInsertRows({}, first, first + 3);
    for (const auto &direction : directions) {
        Bullet bullet;
        bullet.x = column;
        bullet.y = row;
        bullet.directionX = direction[0];
        bullet.directionY = direction[1];
        bullet.lastRow = row;
        bullet.lastColumn = column;
        m_bullets.append(bullet);
    }
    endInsertRows();
    emit countChanged();
}

void BulletModel::removeAt(int index)
{
    if (index < 0 || index >= m_bullets.size())
        return;

    beginRemoveRows({}, index, index);
    m_bullets.removeAt(index);
    endRemoveRows();
    emit countChanged();
}

void BulletModel::notifyPositions()
{
    if (m_bullets.isEmpty())
        return;

    emit dataChanged(index(0), index(int(m_bullets.size()) - 1), { XRole, YRole });
}
