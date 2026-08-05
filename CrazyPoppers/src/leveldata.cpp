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
        makeLevel("The Ring", 4, {
            ".....",
            ".333.",
            ".3.3.",
            "33.33",
            ".3.3.",
            ".333.",
            ".....",
            ".....",
        }),
        makeLevel("The Nest", 5, {
            ".....",
            ".....",
            ".2222",
            ".2442",
            ".2422",
            ".2222",
            ".....",
            ".....",
        }),
        makeLevel("The Fortress", 6, {
            ".....",
            "33333",
            "32223",
            "32423",
            "32223",
            "33333",
            ".....",
            ".....",
        }),
    };
}

} // namespace

const QList<LevelDefinition> &levelLibrary()
{
    static const QList<LevelDefinition> library = buildLibrary();
    return library;
}
