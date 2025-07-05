CC=gcc
CFLAGS=-I./src
SRC=src
MAIN=main
BIN = bin

all: $(BIN) $(BIN)/simple $(BIN)/osc $(BIN)/full

$(BIN):
	mkdir -p $(BIN)

$(BIN)/simple: $(MAIN)/main_simple.c $(SRC)/input_handler.c $(SRC)/keymap.c
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/osc: $(MAIN)/main_osc.c $(SRC)/input_handler.c $(SRC)/keymap.c $(SRC)/osc_handler.c
	$(CC) $(CFLAGS) $^ -llo -o $@

$(BIN)/full: $(MAIN)/main_full.c $(SRC)/input_handler.c $(SRC)/keymap.c $(SRC)/osc_handler.c $(SRC)/mcp3221.c
	$(CC) $(CFLAGS) $^ -llo -o $@

clean:
	rm -rf $(BIN)
