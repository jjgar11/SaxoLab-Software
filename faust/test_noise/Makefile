C_SRC := set_level_noise.c
C_BIN := set_level_noise

BASE_DIR := $(HOME)/faust/test_noise
DSP_FILES := $(wildcard $(BASE_DIR)/*.dsp)
DSP_NAMES := $(basename $(notdir $(DSP_FILES)))
DSP_BINS := $(addprefix $(BASE_DIR)/, $(DSP_NAMES))
CPP_FILES := $(addsuffix .dsp.cpp, $(DSP_NAMES))

.PHONY: all clean

all: $(C_BIN) $(DSP_BINS)

$(C_BIN): $(C_SRC)
	@gcc $< -o $@ -llo && echo "Compilado $@"

$(BASE_DIR)/%: $(BASE_DIR)/%.dsp
	@echo "Procesando $<..."
	@echo "En $(BASE_DIR)/$*..."
	@faust2alsaconsole -osc $<
	@if [ -f $(BASE_DIR)/$* ]; then \
		mv $(BASE_DIR)/$* $@ && echo "Movido ejecutable $* a $(BASE_DIR)"; \
	else \
		echo "No se encontró el ejecutable generado para $<"; \
	fi

clean:
	@rm -f $(C_BIN)
	@echo "$(DSP_BINS)"
	@rm -f $(DSP_BINS)
	@rm -f $(addprefix $(BASE_DIR)/, $(CPP_FILES))
	@echo "Limpieza completa: ejecutables y archivos .cpp eliminados"
