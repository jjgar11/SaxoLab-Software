#include <stdio.h>
#include <stdlib.h>
#include <lo/lo.h>
#include <unistd.h>

#define OSC_PORT "5513"
#define OSC_HOST "localhost"

#define PREFIX "/sax_synth_hslider"
#define GAIN   PREFIX "/gain"
#define NOTE   PREFIX "/note"

int main() {
    lo_address t = lo_address_new(OSC_HOST, OSC_PORT);
    printf("Comenzando programa\n");

    double level = 0;
    lo_send(t, GAIN, "f", level);
    for (int i = 0; i < 10; i++) {
        lo_send(t, GAIN, "f", level);
        printf("Cambiando volumen %f\n", level);
        level += 0.1;
        usleep(200000);
    }
    return 0;
}
