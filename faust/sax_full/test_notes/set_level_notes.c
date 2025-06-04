#include <stdio.h>
#include <stdlib.h>
#include <lo/lo.h>
#include <unistd.h>

#define OSC_PORT "5513"
#define OSC_HOST "localhost"

#define PREFIX "/sax_synth_hslider"
#define GAIN   PREFIX "/gain"
#define NOTE   PREFIX "/note"

void test_volume(lo_address t);
void test_notes(lo_address t);

int main() {
    lo_address t = lo_address_new(OSC_HOST, OSC_PORT);
    printf("Comenzando programa\n");

    test_volume(t);
    test_notes(t);
    return 0;
}

void test_volume(lo_address t) {
    double level = 0;
    lo_send(t, NOTE, "i", 1);
    lo_send(t, GAIN, "f", level);
    for (int i = 0; i < 10; i++) {
        lo_send(t, GAIN, "f", level);
        printf("Cambiando volumen %f\n", level);
        level += 0.1;
        usleep(200000);
    }
    for (int i = 0; i < 10; i++) {
        lo_send(t, GAIN, "f", level);
        printf("Cambiando volumen %f\n", level);
        level -= 0.1;
        usleep(200000);
    }
}

void test_notes(lo_address t) {
    lo_send(t, GAIN, "f", 0.4);
    for (int i = 0; i < 32; i++) {
        lo_send(t, NOTE, "i", i);
        printf("Cambiando nota %d\n", i);
        usleep(500000);
    }
    lo_send(t, GAIN, "f", 0.0);
}
