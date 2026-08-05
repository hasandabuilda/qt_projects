#!/usr/bin/env python3
"""Brute-force solver for Crazy Poppers levels.

Mirrors the rules implemented in src/gameengine.cpp so that every shipped level
can be proven winnable, and so each level's tap budget can be set to the true
minimum number of taps required to clear the board.

Board encoding, one digit per cell:
    0 empty   1 blue   2 green   3 orange   4 red

Rules
-----
* Tapping a creature below red raises it one tier.
* Tapping a red creature pops it and emits one bullet in each cardinal
  direction.
* A bullet advances one cell per simulation step. Entering an occupied cell
  consumes the bullet and hits that creature exactly as a tap would.
* Bullets spawned by a pop begin travelling on the following step, which is what
  the real-time engine does (they appear at rest on the popped cell).
"""

from __future__ import annotations

import sys
from typing import Iterable

DIRECTIONS = ((-1, 0), (1, 0), (0, -1), (0, 1))


def hit(board: list[int], cols: int, index: int, spawned: list) -> None:
    """Apply a tap-equivalent hit to `index`, queuing bullets if it pops."""
    value = board[index]
    if value == 0:
        return
    if value < 4:
        board[index] = value + 1
        return
    board[index] = 0
    row, col = divmod(index, cols)
    for drow, dcol in DIRECTIONS:
        spawned.append((row, col, drow, dcol))


def resolve(board: list[int], rows: int, cols: int, bullets: list) -> None:
    """Run the chain reaction to completion."""
    while bullets:
        advanced: list = []
        spawned: list = []
        for row, col, drow, dcol in bullets:
            nrow, ncol = row + drow, col + dcol
            if not (0 <= nrow < rows and 0 <= ncol < cols):
                continue
            index = nrow * cols + ncol
            if board[index] != 0:
                hit(board, cols, index, spawned)
            else:
                advanced.append((nrow, ncol, drow, dcol))
        bullets = advanced + spawned


def apply_tap(state: tuple[int, ...], rows: int, cols: int, index: int) -> tuple[int, ...]:
    board = list(state)
    bullets: list = []
    hit(board, cols, index, bullets)
    resolve(board, rows, cols, bullets)
    return tuple(board)


class Budget(Exception):
    """Raised when the search exceeds its node allowance."""


def solve(state: tuple[int, ...], rows: int, cols: int, max_taps: int = 8,
          node_limit: int = 40_000_000):
    """Iterative deepening search for the shortest clearing sequence.

    Returns the tap sequence, None if provably unsolvable within `max_taps`, or
    the string "budget" if the search ran out of nodes first.
    """
    for depth in range(1, max_taps + 1):
        failed: set = set()
        path: list[int] = []
        counter = [node_limit]
        try:
            if _search(state, rows, cols, depth, failed, path, counter):
                return path
        except Budget:
            return "budget"
    return None


def _search(state, rows, cols, depth, failed, path, counter) -> bool:
    if not any(state):
        return True
    if depth == 0:
        return False
    key = (state, depth)
    if key in failed:
        return False
    seen: set = set()
    for index, value in enumerate(state):
        if value == 0:
            continue
        counter[0] -= 1
        if counter[0] <= 0:
            raise Budget
        nxt = apply_tap(state, rows, cols, index)
        if nxt in seen:
            continue
        seen.add(nxt)
        path.append(index)
        if _search(nxt, rows, cols, depth - 1, failed, path, counter):
            return True
        path.pop()
    failed.add(key)
    return False


def parse(text: str) -> tuple[tuple[int, ...], int, int]:
    lines = [line.strip() for line in text.strip().splitlines() if line.strip()]
    cols = len(lines[0])
    if any(len(line) != cols for line in lines):
        raise ValueError("ragged grid")
    cells = tuple(0 if ch == "." else int(ch) for line in lines for ch in line)
    return cells, len(lines), cols


def render(state: Iterable[int], cols: int) -> str:
    cells = list(state)
    rows = [cells[i:i + cols] for i in range(0, len(cells), cols)]
    return "\n".join("".join("." if v == 0 else str(v) for v in row) for row in rows)


# The shipped levels, mirroring src/leveldata.cpp. Running this file proves each
# one is clearable and that its tap budget is the true minimum.
LEVELS: dict[str, tuple[int, str]] = {
    "1 First Pop": (1, """
        .....
        .....
        ..4..
        .444.
        ..4..
        .....
        .....
        .....
    """),
    "2 Crossfire": (2, """
        .....
        .3.3.
        .....
        .4.4.
        .....
        .3.3.
        .....
        .....
    """),
    "3 The Lattice": (3, """
        .....
        .3.3.
        33333
        .3.3.
        33433
        .3.3.
        33333
        .....
    """),
    "4 The Ring": (4, """
        .....
        .333.
        .3.3.
        33.33
        .3.3.
        .333.
        .....
        .....
    """),
    "5 The Nest": (5, """
        .....
        .....
        .2222
        .2442
        .2422
        .2222
        .....
        .....
    """),
    "6 The Fortress": (6, """
        .....
        33333
        32223
        32423
        32223
        33333
        .....
        .....
    """),
}


def main() -> int:
    max_taps = int(sys.argv[1]) if len(sys.argv) > 1 else 8
    ok = True
    for name, (budget, text) in LEVELS.items():
        state, rows, cols = parse(text)
        creatures = sum(1 for v in state if v)
        path = solve(state, rows, cols, max_taps)
        print(f"=== {name}  ({rows}x{cols}, {creatures} creatures, budget {budget})")
        print(render(state, cols))
        if path == "budget":
            ok = False
            print("  search budget exhausted\n")
            continue
        if path is None:
            ok = False
            print(f"  UNSOLVABLE within {max_taps} taps\n")
            continue
        moves = ", ".join(f"({i // cols},{i % cols})" for i in path)
        verdict = "OK" if len(path) == budget else f"MISMATCH (shipped budget is {budget})"
        if len(path) != budget:
            ok = False
        print(f"  minimum taps: {len(path)}  [{verdict}]   solution: {moves}\n")
    print("all levels verified" if ok else "PROBLEMS FOUND")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
