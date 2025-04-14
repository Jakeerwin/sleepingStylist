CC = gcc
CFLAGS = -Wall -pthread

SRC = sleepingStylistSem.c
BIN = sleepingStylistSem

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f *.o $(BIN)