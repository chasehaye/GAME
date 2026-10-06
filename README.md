# Traffic Sim

A minimalist road-network strategy game written in C++20 with raylib, inspired by
*Mini Motorways*.

Houses and destinations appear on a grid. The player draws roads to connect them, and
cars drive from homes to the places that need them. The challenge is keeping the
network flowing as the city grows.

> Work in progress. Road drawing and houses are playable; destinations, cars, and
> pathfinding are next.

## Concept

- **Draw roads** by dragging across the grid. A road only exists as part of a drawn
  path: each step of a drag links two neighboring tiles, diagonals included.
- **Houses** each come with their own driveway road. Connect a road to the driveway to
  join the house to the network.
- **Destinations** (in progress) are larger buildings with different footprints. Over
  time they build up demand for cars.
- **Cars** (planned) leave their houses, find a route through the road network to a
  destination that needs them, and return home.
- Later: different kinds of traffic (residential and commercial), a growing map, and
  a lose condition when demand goes unmet for too long.

## Controls

| Input | Action |
| --- | --- |
| Left mouse, drag | Draw road from tile to tile |
| Right mouse, hold | Erase roads under the cursor |
| Esc | Quit |

Erasing a road also removes any road it leaves with no connections at all. A house's
driveway can't be erased.

## Building and running

Requires the [MSYS2](https://www.msys2.org/) UCRT64 toolchain (g++) and raylib:

```
pacman -S mingw-w64-ucrt-x86_64-raylib
```

From the project folder:

```
mingw32-make          # build into build/game.exe
mingw32-make run      # build and run
mingw32-make clean    # remove the build
```

## Architecture

Each frame runs three steps: **input, update, draw**.

```
src/
├── game/        The loop. Owns everything below and runs input -> update -> draw.
├── input/       Reads raw mouse and keyboard state once per frame (InputHandler),
│   └── tools/   decides which tool gets it (PlayerController), and turns it into
│                actions via built in tools.
├── world/       All game state and its rules. No input, screen, or raylib code.
│   ├── map/            The grid of cells.
│   └── worldobjects/   Roads, houses, and the shared WorldObject base.
└── render/      Draws the world (Renderer) and converts between grid cells and
                 screen pixels (PixelMapper). Read-only.
```

Design rules the code follows:

- **World is the single owner.** It creates, owns (`std::unique_ptr`), and removes every
  object, and it's the only code that changes what's on a cell.
- **Objects manage their own data.** A road keeps its links to neighboring roads valid
  on both sides, and unlinks itself in its destructor.
- **Roads form a graph.** Each road links to up to eight neighbors. Pathfinding will
  search this graph from a house's driveway to a destination's entrance.
- **Footprints can be any shape.** A world object covers a list of cells, so buildings
  can be 2x2, 2x3, or irregular.
- **Rendering only reads.** Drawing never changes game state.

## Tech

C++20 · raylib · Make · g++ (MSYS2 UCRT64)
