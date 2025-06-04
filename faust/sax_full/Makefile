BASE_DIR := $(HOME)/faust/sax_full
INPUT_DIR := $(BASE_DIR)/sax_full_faust
OUTPUT_DIR := $(BASE_DIR)/compiled_programs

DSP_FILES := $(wildcard $(INPUT_DIR)/*.dsp)
BINARIES := $(patsubst $(INPUT_DIR)/%.dsp, $(OUTPUT_DIR)/%, $(DSP_FILES))

.PHONY: all clean

all: $(OUTPUT_DIR) $(BINARIES)

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
	rm -rf $(OUTPUT_DIR)

