#include "keymap.h"
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static struct {
    float freq;
    int count;
    const int keys[8];
    const char* name;
} notes[] = {
    {      0, 0, {}, ""},
    {      0, 0, {}, ""},
    { 155.56, 7, {1, 2, 3, 8, 9, 10, 12}, "C : DO"},
    {      0, 0, {}, ""},
    { 174.61, 6, {1, 2, 3, 8, 9, 10}, "D' : RE'"},
    { 184.99, 7, {1, 2, 3, 8, 9, 10, 11}, "Eb : Mib"},
    { 195.99, 5, {1, 2, 3, 8, 9}, "E' : MI'"},
    { 207.65, 4, {1, 2, 3, 8}, "F' : FA'"},
    { 220.00, 4, {1, 2, 3, 9}, "F#' : FA#'"},
    { 233.08, 3, {1, 2, 3}, "G' : SOL'"},
    { 246.94, 5, {1, 2, 3, 15, 16}, "G#' : SOL#'"},
    { 261.63, 2, {1, 2}, "A' : LA'"},
    { 277.18, 3, {1, 2, 22}, "Bb' : SIb'"},
    {      0, 0, {}, ""},
    { 311.13, 1, {1}, "B' : SI'"},
    {      0, 0, {}, ""},
    { 349.23, 7, {1, 2, 3, 8, 9, 10, 16}, "D : RE"},
    { 369.99, 8, {1, 2, 3, 8, 9, 10, 11, 16}, "Eb' : Mib'"},
    { 392.00, 6, {1, 2, 3, 8, 9, 16}, "E' : MI'"},
    { 415.30, 5, {1, 2, 3, 8, 16}, "F' : FA'"},
    { 440.00, 5, {1, 2, 3, 9, 16}, "F#' : FA#'"},
    { 466.16, 4, {1, 2, 3, 16}, "G' : SOL'"},
    { 493.88, 4, {1, 2, 3, 15}, "G#' : SOL#'"},
    { 523.25, 3, {1, 2, 16}, "A' : LA'"},
    { 554.37, 4, {1, 2, 22, 16}, "Bb' : SIb'"},
    { 587.33, 2, {1, 16}, "B' : SI'"},
    {      0, 0, {}, ""},
    { 659.26, 1, {16}, "C#' : DO#'"},
    {      0, 0, {}, ""},
    {      0, 0, {}, ""},
    {      0, 0, {}, ""},
    {      0, 0, {}, ""},
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
