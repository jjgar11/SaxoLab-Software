#include "input_handler.h"
#include "constants.h"
#include <linux/input.h>
#include <stdio.h>

bool keys_pressed[MAX_KEYS] = {false};

int count_pressed_keys() {
    int count = 0;
    for (int i = 0; i < MAX_KEYS; i++) {
        if (keys_pressed[i]) count++;
    }
    return count;
}

void handle_input_event(int code, int value) {
    if (value == 1) {
        keys_pressed[code] = true;
        // printf("Key pressed %d\n", code);
    } else if (value == 0) {
        keys_pressed[code] = false;
        // printf("Key released %d\n", code);
    }
    print_pressed_keys();
}

void print_pressed_keys() {
    printf("Pressed keys : %d  [", count_pressed_keys());
    bool first = true;
    for (int i = 0; i < MAX_KEYS; i++) {
        if (keys_pressed[i]) {
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("]\n");
}