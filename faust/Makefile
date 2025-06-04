SAX_BIN := ./sax_full/compiled_programs/sax_synth_hslider
SAX_TEST := ./sax_full/test_notes/set_level_notes
SAX_NAME := $(notdir $(SAX_BIN))

NOISE_BIN := ./test_noise/noise
NOISE_TEST := ./test_noise/set_level_noise
NOISE_NAME := $(notdir $(NOISE_BIN))

.PHONY: all clean sax_full single_notes test_noise sound noise

all: sax_full single_notes c_only test_noise

sax_full:
	$(MAKE) -C sax_full

single_notes:
	$(MAKE) -C single_notes

test_noise:
	$(MAKE) -C test_noise dsp

c_only:
	$(MAKE) -C sax_full/test_notes
	$(MAKE) -C test_noise c

clean:
	$(MAKE) -C sax_full clean
	$(MAKE) -C sax_full/test_notes clean
	$(MAKE) -C single_notes clean
	$(MAKE) -C test_noise clean

sound:
	@echo "Iniciando sintetizador de saxofón en background..."
	@nohup $(SAX_BIN) -port 5513 > /dev/null 2>&1 &
	@sleep 1
	@$(SAX_TEST)
	@PID=$$(pgrep -f $(SAX_NAME)); \
	if [ -n "$$PID" ]; then \
		echo "Matando proceso con PID: $$PID"; \
		kill $$PID; \
		echo "Finalizado proceso sax_synth_hslider"; \
	else \
		echo "No se encontró proceso $(SAX_NAME) para matar"; \
	fi

noise:
	@echo "Iniciando generador de ruido en background..."
	@nohup $(NOISE_BIN) -port 5513 > /dev/null 2>&1 &
	@sleep 1
	@$(NOISE_TEST)
	@PID=$$(pgrep -f $(NOISE_NAME)); \
	if [ -n "$$PID" ]; then \
		echo "Matando proceso con PID: $$PID"; \
		kill $$PID; \
		echo "Finalizado proceso noise"; \
	else \
		echo "No se encontró proceso $(NOISE_NAME) para matar"; \
	fi
