#pragma once
#include <stdbool.h>

int get_note_index(bool keys_pressed[]);

float get_note_frequency(int note_index);

const char* get_note_name(int note_index);

bool is_exit_combination(bool keys_pressed[]);

int get_random_note_index();
