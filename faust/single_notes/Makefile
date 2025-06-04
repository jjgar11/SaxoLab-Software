BASE_DIR := $(HOME)/faust/single_notes
INPUT_DIR := $(BASE_DIR)/sax_single_notes_faust
OUTPUT_DIR := $(BASE_DIR)/compiled_notes

DSP_FILES := $(wildcard $(INPUT_DIR)/*.dsp)
BINARIES := $(patsubst $(INPUT_DIR)/%.dsp, $(OUTPUT_DIR)/%, $(DSP_FILES))
CPP_FILES := $(patsubst %.dsp, %.dsp.cpp, $(notdir $(DSP_FILES)))

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
		echo "No se encontró el ejecutable $(INPUT_DIR)/$* generado para $<"; \
	fi

clean:
	@rm -rf $(OUTPUT_DIR)
	@rm -f $(addprefix $(INPUT_DIR)/, $(CPP_FILES))
	@echo "Limpieza completa: ejecutables y archivos .cpp eliminados"
