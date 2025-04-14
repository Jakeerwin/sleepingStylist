# Makefile for Sleeping Stylist Assignment

CC = gcc
CFLAGS = -Wall -pthread

# Semaphore version
SEM_SRC = sleepingStylistSem.c
SEM_BIN = sleepingStylistSem

# Monitor version
MON_SRC = sleepingStylistMon.c
MON_OBJS = sleepingStylistMon.o monitor.o
MON_BINSRC = monitor.c
MON_BIN = sleepingStylistMon

all: $(SEM_BIN) $(MON_BIN)

$(SEM_BIN): $(SEM_SRC)
	$(CC) $(CFLAGS) -o $(SEM_BIN) $(SEM_SRC)

$(MON_BIN): $(MON_SRC) $(MON_BINSRC)
	$(CC) $(CFLAGS) -c $(MON_BINSRC) -o monitor.o
	$(CC) $(CFLAGS) -c $(MON_SRC) -o sleepingStylistMon.o
	$(CC) $(CFLAGS) -o $(MON_BIN) $(MON_OBJS)

clean:
	rm -f *.o $(SEM_BIN) $(MON_BIN)
