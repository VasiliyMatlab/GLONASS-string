BIN = ../bin
BUILD = ../build
CC = gcc
FLAGS = -c -Wall
PROJECT = GLONASS_string


all: start program
	@ echo "Building is complete"

start:
	@ echo "Start building"
	../scripts/helper.sh

program: $(BUILD)/main.o $(BUILD)/internal.o
	$(CC) $(BUILD)/main.o $(BUILD)/internal.o -o $(BIN)/$(PROJECT)

$(BUILD)/main.o: main.c internal.h
	$(CC) $(FLAGS) main.c -o $(BUILD)/main.o

$(BUILD)/internal.o: internal.c internal.h
	$(CC) $(FLAGS) internal.c -o $(BUILD)/internal.o


clean:
	rm $(BUILD)/*
	rm $(BIN)/*
