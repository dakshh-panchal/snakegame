CC = g++
CFLAGS = -lraylib -L./

SRC = main.cpp
OUT = app

all: run
run: clean $(OUT)
	./$(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

clean:
	rm -f $(OUT)

