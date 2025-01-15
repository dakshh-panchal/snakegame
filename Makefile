# Compiler and flags
CC = g++
CFLAGS = -lraylib -L/usr/local/lib

# Source file and output executable
SRC = main.cpp
OUT = app

all: run
# Default target: Clean, compile, and run
install: 
	sudo apt install build-essential git
	sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
run: clean $(OUT)
	./$(OUT)

# Compile the program
$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

# Clean up generated files
clean:
	rm -f $(OUT)

