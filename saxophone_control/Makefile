CC=gcc
CFLAGS=-I./src
SRC=src
KEYBOARD=keyboard_test
MAIN=main
BIN = bin

all: $(BIN) $(BIN)/main
test: $(BIN) $(BIN)/simple $(BIN)/osc $(BIN)/full

$(BIN):
	mkdir -p $(BIN)

$(BIN)/simple: $(KEYBOARD)/main_simple.c $(SRC)/input_handler.c $(SRC)/keymap.c
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/osc: $(KEYBOARD)/main_osc.c $(SRC)/input_handler.c $(SRC)/keymap.c $(SRC)/osc_handler.c
	$(CC) $(CFLAGS) $^ -llo -o $@

$(BIN)/full: $(KEYBOARD)/main_full.c $(SRC)/input_handler.c $(SRC)/keymap.c $(SRC)/osc_handler.c $(SRC)/mcp3221.c
	$(CC) $(CFLAGS) $^ -llo -o $@

$(BIN)/main: $(MAIN)/main.c $(SRC)/input_handler.c $(SRC)/keymap.c $(SRC)/osc_handler.c $(SRC)/mcp3221.c $(SRC)/audio.c $(MAIN)/modes.c
	$(CC) $(CFLAGS) $^ -llo -o $@

clean:
	rm -rf $(BIN)
