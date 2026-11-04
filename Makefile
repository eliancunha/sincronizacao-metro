
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -pthread -g

TARGET = sync_car
SOURCES = sync_car.c sync_car-runner.c
HEADERS = sync_car.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f sync_car test_sync_car *.o

.PHONY: all test clean
