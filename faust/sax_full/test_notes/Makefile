C_SRC := set_level_notes.c
BIN := set_level_notes

.PHONY: all clean

all: $(BIN)

$(BIN): $(C_SRC)
	@gcc $< -o $@ -llo && echo "Compilado $@"

clean:
	rm -f $(BIN)
