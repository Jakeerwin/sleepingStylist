# README for Sleeping Stylist Assignment

## Part 1: Semaphore Version (`sleepingStylistSem.c`)

### How to Compile:
```bash
make sleepingStylistSem
```

### How to Run:
```bash
./sleepingStylistSem
```

### What to Observe:
- Customers entering, sitting, and leaving if full
- Stylist cutting hair when customers are present
- No starvation (all 75 customers get haircuts)

---

## Part 2: Monitor Version (`sleepingStylistMon.c` + `monitor.c`)

### How to Compile:
```bash
make sleepingStylistMon
```

### How to Run:
```bash
./sleepingStylistMon
```

### What to Observe:
- Chairs visualized via debug print: `| 1 | 1 | 0 | 0 | ...`
- Haircut count increasing
- Salon full and salon empty counters incrementing
- Signal-and-continue behavior (signaler continues, not the signaled)

---

## Time Spent
- Part 1: X hours
- Part 2: Y hours

## Difficulty (0–5 scale)
- Part 1: N
- Part 2: M