// constants.h
#pragma once

#define MAX_KEYS        256 // Maximum number of keys
#define KEYBOARD_FILE   "/dev/input/event1"
#define OCTAVE_KEY      KEY_Z // Adjust based on your keyboard layout

#define OSC_HOST        "localhost"
#define OSC_PORT        "5513"

#define PREFIX          "/sax_synth_hslider"
#define VOLUME          PREFIX "/gain"
#define NOTE            PREFIX "/note"
#define FREQ            PREFIX "/frequency"

#define MOUTHPIECE      "/dev/i2c-3"


#define CONTROL_TYPE    "idx"    /* or freq */
