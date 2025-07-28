// constants.h
#pragma once

#define MAX_KEYS        20 // Maximum number of keys
#define MAX_COMB_SIZE   8  // Maximum number of keys combination
#define KEYBOARD_FILE   "/dev/input/event1"
#define OCTAVE_KEY      KEY_Z // Adjust based on your keyboard layout

#define OSC_HOST        "localhost"
#define OSC_PORT        "5513"

#define PREFIX          "/sax_synth_hslider"
#define VOLUME          PREFIX "/gain"
#define NOTE            PREFIX "/note"
#define FREQ            PREFIX "/frequency"

#define MOUTHPIECE      "/dev/i2c-3"
#define MCP3221_ADDR    0x4D

#define AUDIO_PREFIX    "audios_wav/"
#define AUDIO_EXT       ".wav"


#define CONTROL_TYPE    "idx"    /* or freq */
