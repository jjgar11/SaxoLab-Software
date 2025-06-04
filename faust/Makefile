.PHONY: all clean sax_full single_notes test_noise

all: sax_full single_notes test_noise

sax_full:
	$(MAKE) -C sax_full
	$(MAKE) -C sax_full/test_notes

single_notes:
	$(MAKE) -C single_notes

test_noise:
	$(MAKE) -C test_noise

clean:
	$(MAKE) -C sax_full clean
	$(MAKE) -C sax_full/test_notes clean
	$(MAKE) -C single_notes clean
	$(MAKE) -C test_noise clean
