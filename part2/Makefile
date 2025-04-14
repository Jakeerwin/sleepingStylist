CC = gcc
CFLAGS = -Wall -pthread

SRC1 = sleepingStylistMon.c
SRC2 = monitor.c
OBJS = sleepingStylistMon.o monitor.o
BIN = sleepingStylistMon

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

sleepingStylistMon.o: $(SRC1)
	$(CC) $(CFLAGS) -c $(SRC1)

monitor.o: $(SRC2)
	$(CC) $(CFLAGS) -c $(SRC2)

clean:
	rm -f *.o $(BIN)