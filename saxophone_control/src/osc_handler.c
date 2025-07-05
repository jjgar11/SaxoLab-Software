#include "osc_handler.h"
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

void osc_send_volume(float volume) {
    lo_send(t, VOLUME, "f", volume);
}
