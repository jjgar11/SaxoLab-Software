#pragma once
#include <stdbool.h>

int get_note_index(bool keys_pressed[], int pressed_count);

float get_note_frequency(int note_index);

const char* get_note_name(int note_index);
