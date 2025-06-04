C_SRC := set_level_noise.c
BIN := set_level_noise

BASE_DIR := $(HOME)/faust/noise
DSP_FILES := $(wildcard $(BASE_DIR)/*.dsp)
BINARIES := $(patsubst $(BASE_DIR)/%.dsp, $(BASE_DIR)/%, $(DSP_FILES))


.PHONY: all clean

all: $(BIN) $(OUTPUT_DIR) $(BINARIES)

$(BIN): $(C_SRC)
	@gcc $< -o $@ -llo && echo "Compilado $@"

$(OUTPUT_DIR):
	@mkdir -p $@
	@echo "Creado directorio $@"

$(OUTPUT_DIR)/%: $(INPUT_DIR)/%.dsp
	@echo "Procesando $<..."
	@echo "En $(INPUT_DIR)/$*..."
	@faust2alsaconsole -osc $<
	@if [ -f $(INPUT_DIR)/$* ]; then \
		mv $(INPUT_DIR)/$* $@ && echo "Movido ejecutable $* a $(OUTPUT_DIR)"; \
	else \
		echo "No se encontró el ejecutable $(INPUT_DIR)$* generado para $<"; \
	fi


clean:
	rm -f $(BIN) $(BINARIES)
