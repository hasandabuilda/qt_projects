# Crazy Poppers

A Qt 6 / QML remake of the old *Crazy Poppers* puzzle game. C++ game engine, Qt Quick
front end, one codebase for desktop and mobile.

## Rules

Creatures sit on a grid in four tiers, each bigger than the last: **blue → green →
orange → red**. Tapping a creature raises it one tier. Tapping a red one pops it in a
puff of white smoke and fires a bullet in each of the four cardinal directions. A
bullet stops at the first creature it meets and hits it exactly as a tap would, so a
single tap can cascade across the whole board.

Clear every creature within the tap budget to win. Run out with creatures still
standing and the level is lost. Input is locked while a cascade resolves, and the
level is only judged once the board goes quiet.

## Screens

Home → level select → game. Pausing gives you resume, restart, level select and home;
clearing a level offers the next one, a replay, or the level list. Progress and best
scores persist through `QSettings`.

## Levels

Six levels, each with a tap budget equal to the *exact minimum* needed to clear it —
no slack, which is what makes them puzzles. Past level 3 the budget stays at three
and the difficulty comes from the board being crowded instead.

| # | Name | Creatures | Touches |
|---|------|-----------|---------|
| 1 | First Pop | 5 | 1 |
| 2 | Crossfire | 6 | 2 |
| 3 | The Lattice | 21 | 3 |
| 4 | The Vault | 32 | 3 |
| 5 | Honeycomb | 36 | 3 |
| 6 | Full House | 40 | 3 |

Two tools back the level design, both re-implementing the engine's rules in Python:

```bash
python tools/level_solver.py   # proves every shipped level's budget is the true minimum
python tools/level_search.py   # hunts for new dense boards with an exact 3-tap minimum
```

Run the solver after editing `src/leveldata.cpp`. It fails loudly if a level becomes
unwinnable or if its budget drifts away from the minimum.

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
tools/                 level verification and search
```

## Notes

Bullets move in continuous grid coordinates and are tested for collision when they
cross a cell boundary. The step per tick is clamped below half a cell so a bullet can
never skip past a creature. Bullets spawned by a pop start moving on the *following*
tick, which is what makes a cascade read as a sequence of pops rather than one flash.

The smoke is a `QtQuick.Particles` emitter using Qt's built-in `fuzzydot` particle
image. Particles blend additively, so the per-particle alpha is deliberately very low
— at anything higher, a burst stacks into one solid white disc rather than smoke.
