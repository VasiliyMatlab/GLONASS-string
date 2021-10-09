BIN = ../bin
BUILD = ../build
CC = gcc
FLAGS = -c -Wall
PROJECT = GLONASS_string


all: start program
	@ echo "Building is complete"

start:
	@ echo "Start building"

program: $(BUILD)/main.o
	$(CC) $(BUILD)/main.o -o $(BIN)/$(PROJECT)

$(BUILD)/main.o: main.c
	$(CC) $(FLAGS) main.c -o $(BUILD)/main.o


clean:
	rm $(BUILD)/*
	rm $(BIN)/*
