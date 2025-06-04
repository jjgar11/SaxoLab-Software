#include <stdio.h>
#include <stdlib.h>
#include <lo/lo.h>
#include <unistd.h>

#define OSC_PORT 5513

void test_volume(lo_address t);
void test_notes(lo_address t);

int main() {
    lo_address t = lo_address_new("localhost", "5513");
    printf("Comenzando programa\n");

    test_volume(t);
    test_notes(t);
    return 0;
}

void test_volume(lo_address t) {
    double level = 0;
    lo_send(t, "/sax_synth_hslider/note", "i", 1);
    lo_send(t, "/sax_synth_hslider/gain", "i", 0);
    for (int i = 0; i < 10; i++) {
        lo_send(t, "/sax_synth_hslider/gain", "f", level);
        printf("Cambiando volumen %f\n", level);
        level += 0.1;
        usleep(100000);
    }
    for (int i = 0; i < 10; i++) {
        lo_send(t, "/sax_synth_hslider/gain", "f", level);
        printf("Cambiando volumen %f\n", level);
        level -= 0.1;
        usleep(100000);
    }
}

void test_notes(lo_address t) {
    lo_send(t, "/sax_synth_hslider/gain", "f", 0.2);
    for (int i = 0; i < 32; i++) {
        lo_send(t, "/sax_synth_hslider/note", "i", i);
        printf("Cambiando nota %d\n", i);
        usleep(500000);
    }
    lo_send(t, "/sax_synth_hslider/gain", "i", 0);
}
