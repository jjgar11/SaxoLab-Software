#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdbool.h>
#include "constants.h"


/*
C:  DO:   W R T U I O M
D:  RE:   W R T U I O
Eb: Mib:  W R T U I O N
E:  MI:   W R T U I
F:  FA:   W R T U
F#: FA#:  W R T I
G:  SOL:  W R T
G#: SOL#: W R T G
A:  LA:   W R
Bb: SIb:  W R V
B:  SI:   W
C:  DO:   R
DO#:


D:  RE':  Z W R T U I O
Eb: Mib': Z W R T U I O N
E:  MI':  Z W R T U I
F:  FA':  Z W R T U
F#: FA#': Z W R T I
G:  SOL': Z W R T
G#: SOL#':Z W R T G
A:  LA':  Z W R
Bb: SIb': Z W R V
B:  SI':  Z W
C:  DO':  Z R
DO#'   :  Z
*/

bool keys_pressed[MAX_KEYS] = {false}; // Array to track pressed keys

int count_pressed_keys() {
    int count = 0;
    for (int i = 0; i < MAX_KEYS; i++) {
        if (keys_pressed[i]) {
            count++;
        }
    }
    return count;
}

void check_saxophone_notes() {
    int pressed_count = count_pressed_keys();

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I] && keys_pressed[KEY_O] &&
        keys_pressed[KEY_N] ){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 8)
            printf("Playing Eb' : Mib'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 7)
            printf("Playing Eb : Mib\nPressed keys : %d\n", pressed_count);

    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I] && keys_pressed[KEY_O] &&
        keys_pressed[KEY_M] &&
        (pressed_count == 7)
        ) {
        printf("Playing C : DO'\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I] && keys_pressed[KEY_O]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 7)
            printf("Playing  D' : RE'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 6)
            printf("Playing  D : RE\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 6)
            printf("Playing  E' : Mi'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 5)
            printf("Playing  E' : Mi\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 5)
            printf("Playing  F' : FA'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 4)
            printf("Playing  F : FA\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_I]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 5)
            printf("Playing  F#' : FA#'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 4)
            printf("Playing  F# : FA#\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_G]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 5)
            printf("Playing  G#' : SOL#'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 4)
            printf("Playing  G# : SOL#\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 4)
            printf("Playing  G' : SOL'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 3)
            printf("Playing  G : SOL\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_V]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 4)
            printf("Playing  Bb' : SIb'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 3)
            printf("Playing  Bb : SIb\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 3)
            printf("Playing  A' : LA'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 2)
            printf("Playing  A : LA\nPressed keys : %d\n", pressed_count);
    }


    if (keys_pressed[KEY_W]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 2)
            printf("Playing   B' : SI'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 1)
            printf("Playing   B : SI\nPressed keys : %d\n", pressed_count);
    }

    if (keys_pressed[KEY_R]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 2)
            printf("Playing   C' : DO'\nPressed keys : %d\n", pressed_count);
          if (pressed_count == 1)
            printf("Playing   C : DO\nPressed keys : %d\n", pressed_count);
    }


    if ( 
        (pressed_count == 1) &&
        keys_pressed[OCTAVE_KEY]) {
        printf("Playing C#' : DO#'\nPressed keys : %d\n", pressed_count);
    }

}

int main() {
    int fd = open(KEYBOARD_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        return EXIT_FAILURE;
    }

    struct input_event ev;

    while (1) {
        ssize_t bytes = read(fd, &ev, sizeof(struct input_event));
        if (bytes == (ssize_t)-1) {
            perror("Error reading");
            close(fd);
            return EXIT_FAILURE;
        }
        if (ev.type == EV_KEY) {
            if (ev.value == 1) { // Key pressed
                keys_pressed[ev.code] = true; // Mark key as pressed
                printf("Key pressed %d\n", ev.code);
            } else if (ev.value == 0) { // Key released
                keys_pressed[ev.code] = false; // Mark key as released
                printf("\n\n");
            }
            check_saxophone_notes(); // Check for notes and count pressed keys
        }
    }
    
    close(fd);
    return EXIT_SUCCESS;
}
