#include "osc_handler.h"
#include "keymap.h"
#include "constants.h"
#include <lo/lo.h>
#include <stdio.h>

static lo_address t;

void osc_init() {
    t = lo_address_new(OSC_HOST, OSC_PORT);
}

void osc_send_note_index(int note_index) {
    lo_send(t, NOTE, "i", note_index);
}

void osc_send_note_freq(float frequency) {
    lo_send(t, FREQ, "f", frequency);
}

void osc_send_volume(float volume) {
    lo_send(t, VOLUME, "f", volume);
}

void osc_send_note(int note_index) {
    if (CONTROL_TYPE == "idx") {
        osc_send_note_index(note_index);
    } else if (CONTROL_TYPE == "freq") {
        osc_send_note_freq(get_note_frequency(note_index));
    }
}
