#include "keymap.h"
#include <linux/input.h>

static struct {
    const int keys[8];
    int count;
    float freq;
    const char* name;
} notes[] = {
    {{6}, 1, 138.59, "Cs3"},
    {{1,2,3,4,5,6}, 6, 146.83, "D3"},
    {{1,2,3,4,5,11}, 6, 155.56, "Ds3"},
    {{1,2,3,4,5}, 5, 164.81, "E3"},
    {{1,2,3,4}, 4, 174.61, "F3"},
    {{1,2,3,4,12}, 5, 185.00, "Fs3"},
    {{1,2,3}, 3, 196.00, "G3"},
    {{1,2,3,4}, 4, 207.65, "Gs3"},
    {{1,2}, 2, 220.00, "A3"},
    {{1,7}, 2, 233.08, "As3"},
    {{1}, 1, 246.94, "B3"},
    {{}, 0, 261.63, "C4"},
    {{6}, 1, 277.18, "Cs4"},
    {{13,1,2,3,4,5,6}, 7, 293.66, "D4"},
    {{13,1,2,3,4,5,11}, 7, 311.13, "Ds4"},
    {{13,1,2,3,4,5}, 6, 329.63, "E4"},
    {{13,1,2,3,4}, 5, 349.23, "F4"},
    {{13,1,2,3,4,12}, 6, 369.99, "Fs4"},
    {{13,1,2,3}, 4, 392.00, "G4"},
    {{13,1,2,3,4}, 5, 415.30, "Gs4"},
    {{13,1,2}, 3, 440.00, "A4"},
    {{13,1,7}, 3, 466.16, "As4"},
    {{13,1}, 2, 493.88, "B4"},
    {{13}, 1, 523.25, "C5"},
    {{13,1,2,11}, 4, 622.25, "Ds5"},
    {{13,1,2}, 3, 659.25, "E5"},
    {{13,1}, 2, 698.46, "F5"},
    {{13,12}, 2, 739.99, "Fs5"},
    {{13,12,14}, 3, 783.99, "G5"},
    {{13,14,15,4}, 4, 830.61, "Gs5"},
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
