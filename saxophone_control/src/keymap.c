#include "keymap.h"
#include <linux/input.h>

static struct {
    const int keys[8];
    int count;
    float freq;
    const char* name;
} notes[] = {
    {{}, 0, 164.8, "Eb : Mib"},
    {{KEY_W, KEY_R, KEY_T, KEY_U, KEY_I, KEY_O, KEY_N}, 7, 184.99, "Eb : Mib"},
    {{KEY_W, KEY_R, KEY_T, KEY_U, KEY_I, KEY_O, KEY_N, KEY_Z}, 8, 369.99, "Eb' : Mib'"},
    {{KEY_W, KEY_R, KEY_T, KEY_U, KEY_I, KEY_O, KEY_M}, 7, 155.56, "C : DO"},
    {{KEY_W, KEY_R, KEY_T, KEY_U, KEY_I, KEY_O, KEY_Z}, 7, 349.23, "D' : RE'"},
    {{KEY_W, KEY_R, KEY_T, KEY_U, KEY_I}, 5, 195.99, "E : MI"},
    {{KEY_W, KEY_R, KEY_T, KEY_U, KEY_I, KEY_Z}, 6, 392.00, "E' : MI'"},
    {{KEY_W, KEY_R, KEY_T, KEY_U}, 4, 207.65, "F : FA"},
    {{KEY_W, KEY_R, KEY_T, KEY_U, KEY_Z}, 5, 415.30, "F' : FA'"},
    {{KEY_W, KEY_R, KEY_T, KEY_I}, 4, 220.00, "F# : FA#"},
    {{KEY_W, KEY_R, KEY_T, KEY_I, KEY_Z}, 5, 440.00, "F#' : FA#'"},
    {{KEY_W, KEY_R, KEY_T}, 3, 233.08, "G : SOL"},
    {{KEY_W, KEY_R, KEY_T, KEY_Z}, 4, 466.16, "G' : SOL'"},
    {{KEY_W, KEY_R, KEY_T, KEY_G}, 4, 246.94, "G# : SOL#"},
    {{KEY_W, KEY_R, KEY_T, KEY_G, KEY_Z}, 5, 493.88, "G#' : SOL#'"},
    {{KEY_W, KEY_R}, 2, 261.63, "A : LA"},
    {{KEY_W, KEY_R, KEY_Z}, 3, 523.25, "A' : LA'"},
    {{KEY_W, KEY_R, KEY_V}, 3, 277.18, "Bb : SIb"},
    {{KEY_W, KEY_R, KEY_V, KEY_Z}, 4, 554.37, "Bb' : SIb'"},
    {{KEY_Z, KEY_A, KEY_W}, 3, 659.26, "C#' : DO#'"},
    {{KEY_W}, 1, 293.66, "B : SI"},
    {{KEY_W, KEY_Z}, 2, 587.33, "B' : SI'"},
    {{KEY_R}, 1, 311.13, "C : DO"},
    {{KEY_R, KEY_Z}, 2, 622.25, "C' : DO'"},
    {{KEY_Z}, 1, 659.26, "C#' : DO#'"},
    {{KEY_V, KEY_T, KEY_F}, 3, 659.26, "C#' : DO#'"}
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
