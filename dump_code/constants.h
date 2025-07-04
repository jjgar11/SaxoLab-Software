
#define KEYBOARD_FILE   "/dev/input/event1"
#define MOUTHPIECE      "/dev/i2c-3"

#define MAX_KEYS 256 // Maximum number of keys
#define OCTAVE_KEY KEY_Z // Adjust based on your keyboard layout

#define OSC_HOST "localhost"
#define OSC_PORT "5513"

#define PREFIX "/sax_synth_hslider"
#define VOLUME   PREFIX "/gain"
#define NOTE     PREFIX "/note"
