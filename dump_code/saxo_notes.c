#include <stdio.h>
#include <stdlib.h>
#include <lo/lo.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdbool.h>
#include <math.h>

#define OSC_PORT 5513
#define MAX_KEYS 256 // Maximum number of keys
#define OCTAVE_KEY KEY_Z // Adjust based on your keyboard layout


/*
Low SIb Bb    : 138.59 Hz
Low SI  B     : 146.83 Hz 
Low DO  C     : 155.56 Hz 
Low DO# C#/Db : 164.81 Hz 
Low D RE      : 174.61 Hz 
Low MIb D#/Eb : 184.99 Hz 
Low MI E      : 195.99 Hz 
Low FA F      : 207.65 Hz 
Low FA# F#/Gb : 220.00 Hz
Low SOL G     : 233.08 Hz
Low SOL# G#/Ab: 246.94 Hz
Low LA A      : 261.63 Hz
Low SIb A#/Bb : 277.18 Hz
Mid SI B      : 293.66 Hz
Mid DO C      : 311.13 Hz
Mid DO# C#/Db : 329.63 Hz
Mid RE D      : 349.23 Hz
Mid MIb D#/Eb : 369.99 Hz
Mid MI E      : 392.00 Hz
Mid FA F      : 415.30 Hz
Mid FA# F#/Gb : 440.00 Hz
Mid SOL G     : 466.16 Hz
Mid SOL# G#/Ab: 493.88 Hz
Mid LA A      : 523.25 Hz
Mid SIb A#/Bb : 554.37 Hz
High SI B     : 587.33 Hz 
High DO C     : 622.25 Hz 
High DO# C#/Db: 659.26 Hz 
High RE D     : 698.46 Hz 
High RE# D#/Eb: 739.99 Hz
High MI E     : 783.99 Hz
High FA F     : 830.61 Hz
High FA# F#   : 880.00 Hz 



A  B  C  D  E  F  G
LA SI DO RE MI FA SOL

C:  DO:   W R T U I O M    155.56 Hz
D:  RE:   W R T U I O      174.61 Hz
Eb: Mib:  W R T U I O N    184.99 Hz
E:  MI:   W R T U I        195.99 Hz
F:  FA:   W R T U          207.65 Hz
F#: FA#:  W R T I          220.00 Hz
G:  SOL:  W R T            233.082Hz
G#: SOL#: W R T G          246.94 Hz
A:  LA:   W R              261.63 Hz
Bb: SIb:  W R V            277.18 Hz
B:  SI:   W                293.66 Hz
C:  DO:   R                311.13 Hz
DO#:                       329.63 Hz


D':  RE':  Z W R T U I O   349.23 Hz
Eb': Mib': Z W R T U I O N 369.99 Hz
E':  MI':  Z W R T U I     392.00 Hz
F':  FA':  Z W R T U       415.30 Hz
F#': FA#': Z W R T I       440.00 Hz
G':  SOL': Z W R T         466.16 Hz
G#': SOL#':Z W R T G       493.88 Hz
A':  LA':  Z W R           523.25 Hz
Bb': SIb': Z W R V         554.37 Hz
B':  SI':  Z W             587.33 Hz 
C':  DO':  Z R             622.25 Hz 
DO#'    :  Z               659.26 Hz 
*/

bool keys_pressed[MAX_KEYS] = {false}; // Array to track pressed keys
lo_address t;

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
    double frequency_note;

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I] && keys_pressed[KEY_O] &&
        keys_pressed[KEY_N] ){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 8){
            printf("Playing Eb' : Mib'\n");
            frequency_note = 369.99;
          }
          if (pressed_count == 7){
            frequency_note = 184.99;
            printf("Playing Eb : Mib\n");
          }

    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I] && keys_pressed[KEY_O] &&
        keys_pressed[KEY_M] &&
        (pressed_count == 7)
        ) {
          printf("Playing C : DO'\n");
          frequency_note = 155.56;
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I] && keys_pressed[KEY_O]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 7){
            frequency_note = 349.23;   
            printf("Playing  D' : RE'\n");
          }
          if (pressed_count == 6){
            frequency_note = 174.61; 
            printf("Playing  D : RE\n");
          }
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U] && keys_pressed[KEY_I]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 6){
            frequency_note = 392.00;
            printf("Playing  E' : Mi'\n");
          }
          if (pressed_count == 5){ 
            frequency_note = 195.99;
            printf("Playing  E : Mi\n");
          }
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_U]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 5){
            frequency_note = 415.30;
            printf("Playing  F' : FA'\n");
          }
          if (pressed_count == 4){
            frequency_note = 207.65;
            printf("Playing  F : FA\n");
          }
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_I]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 5){
            frequency_note = 440.00;
            printf("Playing  F#' : FA#'\n");
          }
          if (pressed_count == 4){
            frequency_note = 220.00;
            printf("Playing  F# : FA#\n");
          }
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T] && 
        keys_pressed[KEY_G]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 5){
            frequency_note = 493.88;
            printf("Playing  G#' : SOL#'\n");
          }
          if (pressed_count == 4){
            frequency_note = 246.94;
            printf("Playing  G# : SOL#\n");
          }
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_T]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 4){
            frequency_note = 466.16;
            printf("Playing  G' : SOL'\n");
          }
          if (pressed_count == 3){
            frequency_note = 233.08;
            printf("Playing  G : SOL\n");
          }
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R] && keys_pressed[KEY_V]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 4){
            frequency_note = 554.37;
            printf("Playing  Bb' : SIb'\n");
          }
          if (pressed_count == 3){
            frequency_note = 277.18;
            printf("Playing  Bb : SIb\n");
          }
    }

    if (keys_pressed[KEY_W] && keys_pressed[KEY_R]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 3){
            frequency_note = 523.25;
            printf("Playing  A' : LA'\n");
          }
          if (pressed_count == 2){
            frequency_note = 261.63;
            printf("Playing  A : LA\n");
          }
    }


    if (keys_pressed[KEY_W]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 2){
            frequency_note = 587.33;
            printf("Playing   B' : SI'\n");
          }
          if (pressed_count == 1){
            frequency_note = 293.66;
            printf("Playing   B : SI\n");
          }
    }

    if (keys_pressed[KEY_R]){
        if(keys_pressed[OCTAVE_KEY])
          if (pressed_count == 2){
            frequency_note = 622.25;
            printf("Playing   C' : DO'\n");
          }
          if (pressed_count == 1){
            frequency_note = 311.13;
            printf("Playing   C : DO\n");
          }
    }


    if ( (pressed_count == 1) &&
        keys_pressed[OCTAVE_KEY]) {
            frequency_note = 659.26;
            printf("Playing C#' : DO#'\n");
    }

    lo_send(t, "/note/frequency", "f", frequency_note);

}

int main() {
    int fd = open("/dev/input/event0", O_RDONLY);
    t = lo_address_new("localhost", "5513");
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
            } else if (ev.value == 0) { // Key released
                keys_pressed[ev.code] = false; // Mark key as released
                int pressed_count = count_pressed_keys();
                if(pressed_count == 0)
                  lo_send(t, "/note/frequency", "f", 0);
            }
            check_saxophone_notes(); // Check for notes and count pressed keys
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}