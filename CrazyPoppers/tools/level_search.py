#!/usr/bin/env python3
"""Search for dense levels that are winnable in exactly three taps.

The interesting difficulty in this game does not come from a long tap budget —
it comes from a crowded board where only a few opening taps cascade all the way
through. This generates mirror-symmetric boards so they read as designed rather
than random, then keeps the ones whose true minimum is exactly three taps.

    python tools/level_search.py [iterations]
"""

from __future__ import annotations

import random
import sys

from level_solver import render, solve

ROWS = 8
COLS = 5


def mirrored(rng: random.Random, rows: range, density: float,
             weights: list[int], vertical: bool) -> tuple[int, ...]:
    cells = [0] * (ROWS * COLS)
    half = (COLS + 1) // 2
    row_list = list(rows)
    for index, row in enumerate(row_list):
        if vertical and index > len(row_list) // 2:
            break
        for column in range(half):
            tier = rng.choices([1, 2, 3, 4], weights=weights)[0] if rng.random() < density else 0
            targets = [(row, column), (row, COLS - 1 - column)]
            if vertical:
                mirror_row = row_list[len(row_list) - 1 - index]
                targets += [(mirror_row, column), (mirror_row, COLS - 1 - column)]
            for r, c in targets:
                cells[r * COLS + c] = tier
    return tuple(cells)


def main() -> int:
    iterations = int(sys.argv[1]) if len(sys.argv) > 1 else 40000
    rng = random.Random(20260804)

    regions = [range(0, 8), range(1, 7), range(0, 7), range(1, 8)]
    weight_sets = [[1, 2, 5, 4], [1, 1, 6, 4], [2, 3, 5, 3], [0, 1, 5, 5]]

    found: dict[tuple[int, ...], int] = {}
    for step in range(iterations):
        rows = rng.choice(regions)
        weights = rng.choice(weight_sets)
        density = rng.uniform(0.72, 1.0)
        vertical = rng.random() < 0.5
        state = mirrored(rng, rows, density, weights, vertical)

        creatures = sum(1 for v in state if v)
        if creatures < 24:
            continue
        if state in found:
            continue

        path = solve(state, ROWS, COLS, 3, node_limit=400_000)
        if isinstance(path, list) and len(path) == 3:
            found[state] = creatures

        if (step + 1) % 5000 == 0:
            print(f"  ...{step + 1} tried, {len(found)} keepers", flush=True)

    ranked = sorted(found.items(), key=lambda kv: -kv[1])
    print(f"\n{len(ranked)} boards with an exact 3-tap minimum\n")
    for state, creatures in ranked[:12]:
        path = solve(state, ROWS, COLS, 3, node_limit=400_000)
        moves = ", ".join(f"({i // COLS},{i % COLS})" for i in path)
        print(f"--- {creatures} creatures   solution: {moves}")
        print(render(state, COLS))
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
