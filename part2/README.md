# Sleeping Stylist Monitor Version (Part 2)

## Name
Jake Erwin (worked solo)

## Instructions

**Make sure you are in the following directory before running any commands:**
```
cd Erwin_Jake_Assignment2/part2
```

## How to Compile:
```bash
make
```

## How to Run:
```bash
./sleepingStylistMon
```

## Cleaning Up:
```bash
make clean
```

## What to Observe:
- Chairs visualized via debug print: `| 1 | 1 | 0 | 0 | ...`
- Haircut count increasing
- Salon full and salon empty counters incrementing
- Signal-and-continue behavior is followed: the signaling thread continues inside the monitor, while the signaled thread waits at the entry queue. You can observe this via lack of overlapping debug output or additional `printf` logs in `waitCV`/`signalCV` if enabled.

## Time Spent
- Part 2: 7 hours

## Difficulty (0–5 scale)
- Part 2: 5
