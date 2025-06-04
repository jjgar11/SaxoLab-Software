#include <stdio.h>
#include <stdlib.h>
#include <lo/lo.h>
#include <unistd.h>

#define OSC_PORT "5513"
#define OSC_HOST "localhost"

#define PREFIX "/noise"
#define GAIN   PREFIX "/level"

int main() {
    lo_address t = lo_address_new(OSC_HOST, OSC_PORT);
    printf("Comenzando programa\n");

    double level = 0;
    lo_send(t, GAIN, "f", level);
    for (int i = 0; i <= 50; i++) {
        lo_send(t, GAIN, "f", level);
        printf("Cambiando volumen %f\n", level);
        level += 0.02;
        usleep(50000);
    }
    lo_send(t, GAIN, "f", 0);
    return 0;
}
