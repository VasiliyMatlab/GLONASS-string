BIN = ../bin
BUILD = ../build
CC = gcc
PROJECT = GLONASS_string
СFLAGS = -c -Wall -Werror -std=gnu17 -O3
LDFLAGS = -g -Wall -Werror -std=gnu17 -O3


all: start program
	@ echo "Building is complete"

start:
	@ echo "Start building"
	mkdir -pv ../build
	mkdir -pv ../bin

program: $(BUILD)/main.o $(BUILD)/internal.o
	$(CC) $(LDFLAGS) $(BUILD)/main.o $(BUILD)/internal.o -o $(BIN)/$(PROJECT)

$(BUILD)/main.o: main.c internal.h
	$(CC) $(СFLAGS) main.c -o $(BUILD)/main.o

$(BUILD)/internal.o: internal.c internal.h
	$(CC) $(СFLAGS) internal.c -o $(BUILD)/internal.o


archiving:
	cd $(BIN)/ && tar -zcvf Binaries.tar.gz $(PROJECT)

clean:
	rm -rv $(BUILD)
	rm -rv $(BIN)
