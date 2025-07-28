#include "keymap.h"
#include "constants.h"
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static struct {
    float freq;
    const int keys[MAX_COMB_SIZE];
    const char* name;
} notes[] = {
    {      0, { }, ""},
    {      0, { }, ""},
    { 155.56, {1, 2, 3, 8, 9, 10, 12}, "C : DO"},
    {      0, { }, ""},
    { 174.61, {1, 2, 3, 8, 9, 10}, "D' : RE'"},
    { 184.99, {1, 2, 3, 8, 9, 10, 11}, "Eb : Mib"},
    { 195.99, {1, 2, 3, 8, 9}, "E' : MI'"},
    { 207.65, {1, 2, 3, 8}, "F' : FA'"},
    { 220.00, {1, 2, 3, 9}, "F#' : FA#'"},
    { 233.08, {1, 2, 3}, "G' : SOL'"},
    { 246.94, {1, 2, 3, 15, 16}, "G#' : SOL#'"},
    { 261.63, {1, 2}, "A' : LA'"},
    { 277.18, {1, 2, 22}, "Bb' : SIb'"},
    {      0, { }, ""},
    { 311.13, {1}, "B' : SI'"},
    {      0, { }, ""},
    { 349.23, {1, 2, 3, 8, 9, 10, 16}, "D : RE"},
    { 369.99, {1, 2, 3, 8, 9, 10, 11, 16}, "Eb' : Mib'"},
    { 392.00, {1, 2, 3, 8, 9, 16}, "E' : MI'"},
    { 415.30, {1, 2, 3, 8, 16}, "F' : FA'"},
    { 440.00, {1, 2, 3, 9, 16}, "F#' : FA#'"},
    { 466.16, {1, 2, 3, 16}, "G' : SOL'"},
    { 493.88, {1, 2, 3, 15}, "G#' : SOL#'"},
    { 523.25, {1, 2, 16}, "A' : LA'"},
    { 554.37, {1, 2, 22, 16}, "Bb' : SIb'"},
    { 587.33, {1, 16}, "B' : SI'"},
    {      0, { }, ""},
    { 659.26, {16}, "C#' : DO#'"},
    {      0, { }, ""},
    {      0, { }, ""},
    {      0, { }, ""},
    {      0, { }, ""},
};

const int notes_count = sizeof(notes) / sizeof(notes[0]);

int get_note_index(bool keys_pressed[]) {
    for (int i = 0; i < notes_count; i++) {
        bool match = true;

        for (int j = 0; j < MAX_COMB_SIZE; j++) {
            int key = notes[i].keys[j];
            if (key == 0) break;
            if (!keys_pressed[key]) {
                match = false;
                break;
            }
        }

        if (match) {
            for (int k = 0; k < MAX_KEYS; k++) {
                if (keys_pressed[k]) {
                    bool expected = false;
                    for (int j = 0; j < MAX_COMB_SIZE && notes[i].keys[j] != 0; j++) {
                        if (notes[i].keys[j] == k) {
                            expected = true;
                            break;
                        }
                    }
                    if (!expected) {
                        match = false;
                        break;
                    }
                }
            }
        }
        if (match) return i;
    }
    return -1;
}

float get_note_frequency(int note_index) {
    return (note_index >= 0) ? notes[note_index].freq : 0;
}

const char* get_note_name(int note_index) {
    return (note_index >= 0) ? notes[note_index].name : "";
}

bool is_exit_combination(bool keys_pressed[]) {
    static const int exit_keys[] = {13, 14, 15, 16};
    for (int i = 0; i < 4; i++) {
        if (!keys_pressed[exit_keys[i]]) return false;
    }
    return true;
}

int get_random_note_index() {
    int idx;
    do {
        idx = rand() % notes_count;
    } while (get_note_frequency(idx) == 0);
    return idx;
}
