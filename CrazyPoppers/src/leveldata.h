#pragma once

#include <QList>
#include <QString>

/*!
    A single puzzle layout.

    \c cells holds \c rows * \c columns tiers in row-major order, where 0 is an
    empty cell and 1..4 are blue, green, orange and red creatures.

    \c taps is the exact minimum number of taps needed to clear the board, as
    proven by tools/level_solver.py. Levels ship with no slack, which is what
    makes them puzzles rather than clicking exercises.
*/
struct LevelDefinition
{
    QString name;
    int rows = 0;
    int columns = 0;
    int taps = 0;
    QList<int> cells;
};

const QList<LevelDefinition> &levelLibrary();
