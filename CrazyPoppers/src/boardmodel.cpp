#include "boardmodel.h"

#include "leveldata.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int BoardModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : int(m_cells.size());
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_cells.size())
        return {};

    switch (role) {
    case TierRole:
        return m_cells.at(index.row());
    case RowRole:
        return m_columns > 0 ? index.row() / m_columns : 0;
    case ColumnRole:
        return m_columns > 0 ? index.row() % m_columns : 0;
    default:
        return {};
    }
}

QHash<int, QByteArray> BoardModel::roleNames() const
{
    return {
        { TierRole, "tier" },
        { RowRole, "cellRow" },
        { ColumnRole, "cellColumn" },
    };
}

void BoardModel::load(const LevelDefinition &level)
{
    beginResetModel();
    m_cells = level.cells;
    m_rows = level.rows;
    m_columns = level.columns;
    m_creatureCount = 0;
    for (int tier : std::as_const(m_cells)) {
        if (tier > 0)
            ++m_creatureCount;
    }
    endResetModel();

    emit dimensionsChanged();
    emit creatureCountChanged();
}

bool BoardModel::contains(int row, int column) const
{
    return row >= 0 && row < m_rows && column >= 0 && column < m_columns;
}

int BoardModel::tierAt(int index) const
{
    return index >= 0 && index < m_cells.size() ? m_cells.at(index) : 0;
}

void BoardModel::setTierAt(int index, int tier)
{
    if (index < 0 || index >= m_cells.size() || m_cells.at(index) == tier)
        return;

    const bool wasOccupied = m_cells.at(index) > 0;
    const bool isOccupied = tier > 0;
    m_cells[index] = tier;

    const QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { TierRole });

    if (wasOccupied != isOccupied) {
        m_creatureCount += isOccupied ? 1 : -1;
        emit creatureCountChanged();
    }
}
