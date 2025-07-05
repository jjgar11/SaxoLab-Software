#pragma once
#include <stdbool.h>

extern bool keys_pressed[];

int count_pressed_keys();

void handle_input_event(int code, int value);
