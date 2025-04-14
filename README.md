# Sleeping Stylist Assignment - Semaphore & Monitor Versions

## Name
Jake Erwin (worked solo)

---

## Part 1: Semaphore Version

### Instructions
**Make sure you are in the following directory before running any commands:**
```
cd Erwin_Jake_Assignment2/part1
```

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

## Part 2: Monitor Version

### Instructions
**Make sure you are in the following directory before running any commands:**
```
cd Erwin_Jake_Assignment2/part2
```

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