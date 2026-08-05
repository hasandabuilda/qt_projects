#include "leveldata.h"

#include <cstring>
#include <initializer_list>

namespace {

LevelDefinition makeLevel(const char *name, int taps,
                          std::initializer_list<const char *> rows)
{
    LevelDefinition level;
    level.name = QString::fromUtf8(name);
    level.taps = taps;
    level.rows = int(rows.size());
    level.columns = int(std::strlen(*rows.begin()));
    level.cells.reserve(level.rows * level.columns);

    for (const char *row : rows) {
        for (int column = 0; column < level.columns; ++column) {
            const char cell = row[column];
            level.cells.append(cell == '.' ? 0 : cell - '0');
        }
    }
    return level;
}

// Every tap budget below is the exact minimum found by tools/level_solver.py,
// so each level is winnable and none of them can be brute-forced.
QList<LevelDefinition> buildLibrary()
{
    return {
        makeLevel("First Pop", 1, {
            ".....",
            ".....",
            "..4..",
            ".444.",
            "..4..",
            ".....",
            ".....",
            ".....",
        }),
        makeLevel("Single Pop", 3, {
              ".....",
              ".....",
              ".....",
              "..2..",
              ".....",
              ".....",
              ".....",
              ".....",
          }),
        makeLevel("Chain Reaction", 1, {
               ".....",
               ".....",
               "..4..",
               "..4..",
               "..4..",
               "..2..",
               ".....",
               ".....",
           }),
        makeLevel("Crossfire", 2, {
            ".....",
            ".3.3.",
            ".....",
            ".4.4.",
            ".....",
            ".3.3.",
            ".....",
            ".....",
        }),
        makeLevel("Step Up", 3, {
            ".....",
            "4.3.4",
            "..4..",
            "..2..",
            "3.3.3",
            "..2..",
            "..4..",
            "4.3.4",
        }),
        makeLevel("The Lattice", 3, {
            ".....",
            ".3.3.",
            "33333",
            ".3.3.",
            "33433",
            ".3.3.",
            "33333",
            ".....",
        }),
        // From here on the tap budget stays at three and the difficulty comes
        // from the board being crowded — far more creatures, far fewer opening
        // taps that cascade all the way through. Found by tools/level_search.py.
        makeLevel("The Vault", 3, {
            "33333",
            "33333",
            "4...4",
            "33.33",
            "33.33",
            "4...4",
            "33333",
            "33333",
        }),
        makeLevel("Honeycomb", 3, {
            "43334",
            "3.3.3",
            "33433",
            "22322",
            "22322",
            "33433",
            "3.3.3",
            "43334",
        }),
        makeLevel("Full House", 3, {
            "41414",
            "33433",
            "42224",
            "33333",
            "33333",
            "42224",
            "33433",
            "41414",
        }),
    };
}

} // namespace

const QList<LevelDefinition> &levelLibrary()
{
    static const QList<LevelDefinition> library = buildLibrary();
    return library;
}
