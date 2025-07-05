#include "keymap.h"
#include <linux/input.h>

static struct {
    const int keys[8];
    int count;
    float freq;
    const char* name;
} notes[] = {
    {{  }, 0, 164.88, "Cs3"},
    {{ 1}, 1, 184.99, "D3"},
    {{ 2}, 1, 369.99, "Ds3"},
    {{ 3}, 1, 155.56, "E3"},
    {{ 4}, 1, 349.23, "F3"},
    {{ 5}, 1, 195.99, "Fs3"},
    {{ 6}, 1, 392.00, "G3"},
    {{ 7}, 1, 207.65, "Gs3"},
    {{ 8}, 1, 415.30, "A3"},
    {{ 9}, 1, 220.00, "As3"},
    {{10}, 1, 440.00, "B3"},
    {{11}, 1, 233.08, "C4"},
    {{12}, 1, 466.16, "Cs4"},
    {{13}, 1, 246.94, "D4"},
    {{14}, 1, 493.88, "Ds4"},
    {{15}, 1, 261.63, "E4"},
    {{16}, 1, 523.25, "F4"},
    {{ 1,  2}, 2, 261.63, "Fs4"},
    {{ 1,  3}, 2, 261.63, "G4"},
    {{ 1,  4}, 2, 261.63, "Gs4"},
    {{ 1,  5}, 2, 261.63, "A4"},
    {{ 1,  6}, 2, 261.63, "As4"},
    {{ 1,  7}, 2, 261.63, "B4"},
    {{ 1,  8}, 2, 261.63, "C5"},
    {{ 1,  9}, 2, 261.63, "Cs5"},
    {{ 1, 10}, 2, 261.63, "D5"},
    {{ 1, 11}, 2, 261.63, "Ds5"},
    {{ 1, 12}, 2, 261.63, "E5"},
    {{ 1, 13}, 2, 261.63, "F5"},
    {{ 1, 14}, 2, 261.63, "Fs5"},
    {{ 1, 15}, 2, 261.63, "G5"},
    {{ 1, 16}, 2, 261.63, "Gs5"}
};

int get_note_index(bool keys_pressed[], int pressed_count) {
    for (int i = 0; i < sizeof(notes)/sizeof(notes[0]); i++) {
        if (notes[i].count == pressed_count) {
            bool match = true;
            for (int j = 0; j < notes[i].count; j++) {
                if (!keys_pressed[notes[i].keys[j]]) {
                    match = false;
                    break;
                }
            }
            if (match) return i;
        }
    }
    return -1;
}

float get_note_frequency(int note_index) {
    return (note_index >= 0) ? notes[note_index].freq : 0;
}

const char* get_note_name(int note_index) {
    return (note_index >= 0) ? notes[note_index].name : "";
}
