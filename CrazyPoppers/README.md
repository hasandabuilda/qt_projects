# Crazy Poppers

A Qt 6 / QML remake of the old *Crazy Poppers* puzzle game. C++ game engine, Qt Quick
front end, one codebase for desktop and mobile.

## Rules

Creatures sit on a grid in four tiers, each bigger than the last: **blue → green →
orange → red**. Tapping a creature raises it one tier. Tapping a red one pops it and
fires a bullet in each of the four cardinal directions. A bullet stops at the first
creature it meets and hits it exactly as a tap would, so a single tap can cascade
across the board.

Clear every creature within the tap budget to win. Run out with creatures still
standing and the level is lost. Input is locked while a cascade resolves, and the
level is only judged once the board goes quiet.

## Levels

Six levels, each with a tap budget equal to the *exact minimum* needed to clear it —
no slack, which is what makes them puzzles.

| # | Name | Creatures | Touches |
|---|------|-----------|---------|
| 1 | First Pop | 5 | 1 |
| 2 | Crossfire | 6 | 2 |
| 3 | The Lattice | 21 | 3 |
| 4 | The Ring | 14 | 4 |
| 5 | The Nest | 16 | 5 |
| 6 | The Fortress | 25 | 6 |

`tools/level_solver.py` re-implements the rules and brute-forces the shortest
clearing sequence for every level. Run it after editing `src/leveldata.cpp` to prove
levels are still winnable and that the budgets are still minimal:

```bash
python tools/level_solver.py
```

## Building

Open `CMakeLists.txt` in Qt Creator and pick a Qt 6.8+ kit, or from the command line:

```bash
qt-cmake -S CrazyPoppers -B CrazyPoppers-build -G Ninja && cmake --build CrazyPoppers-build
```

The executable is built as a console-subsystem binary so QML warnings show up in Qt
Creator's Application Output. For a release build, add `WIN32_EXECUTABLE TRUE` /
`MACOSX_BUNDLE TRUE` via `set_target_properties` to drop the console window.

## Layout

```
src/
  gameengine.{h,cpp}   rules, cascade simulation, scoring, progress
  boardmodel.{h,cpp}   row-major grid of creature tiers
  bulletmodel.{h,cpp}  projectiles in flight
  leveldata.{h,cpp}    the six level definitions
qml/CrazyPoppers/      Qt Quick UI, one QML module
tools/level_solver.py  level verification
```

Progress and best scores persist through `QSettings`.

## Notes

Bullets move in continuous grid coordinates and are tested for collision when they
cross a cell boundary. The step per tick is clamped below half a cell so a bullet can
never skip past a creature. Bullets spawned by a pop start moving on the *following*
tick, which is what makes a cascade read as a sequence of pops rather than one flash.
