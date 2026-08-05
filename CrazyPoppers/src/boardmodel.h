#pragma once

#include <QAbstractListModel>
#include <QtQmlIntegration/qqmlintegration.h>

struct LevelDefinition;

/*!
    Flat row-major model of the playfield, one item per grid cell.

    Empty cells stay in the model rather than being removed, so a cell's index
    is stable for the lifetime of a level and QML delegates can animate a
    creature out instead of being destroyed under it.
*/
class BoardModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(int rows READ rows NOTIFY dimensionsChanged)
    Q_PROPERTY(int columns READ columns NOTIFY dimensionsChanged)
    Q_PROPERTY(int creatureCount READ creatureCount NOTIFY creatureCountChanged)

public:
    enum Role {
        TierRole = Qt::UserRole + 1,
        RowRole,
        ColumnRole,
    };

    explicit BoardModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int rows() const { return m_rows; }
    int columns() const { return m_columns; }
    int creatureCount() const { return m_creatureCount; }

    void load(const LevelDefinition &level);

    bool contains(int row, int column) const;
    int indexOf(int row, int column) const { return row * m_columns + column; }
    int tierAt(int index) const;
    void setTierAt(int index, int tier);

signals:
    void dimensionsChanged();
    void creatureCountChanged();

private:
    QList<int> m_cells;
    int m_rows = 0;
    int m_columns = 0;
    int m_creatureCount = 0;
};
