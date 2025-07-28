#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "../src/input_handler.h"
#include "../src/keymap.h"
#include "../src/osc_handler.h"
#include "../src/mcp3221.h"
#include "../src/audio.h"
#include "../src/constants.h"


void free_mode(int fd) {
    start_faust();

    pthread_t thread;
    pthread_create(&thread, NULL, pressure_loop, NULL);

    struct input_event ev;
    double volume = 0;
    printf("base volume: %.2lf\n", volume);

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            handle_input_event(ev.code, ev.value);

            int idx = get_note_index(keys_pressed);

            if (idx >= 0) {
                osc_send_note(idx);
                printf("Playing %s\tAt %f Hz\n", 
                    get_note_name(idx), 
                    get_note_frequency(idx), 
                    volume);
            }
        }
    }
    stop_faust();
}

void training_mode(int fd) {

}
