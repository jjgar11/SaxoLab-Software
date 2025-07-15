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
#include "../src/constants.h"

void* pressure_loop(void* arg) {
    while (1) {
        int gain = mouthpiece_gain();
        double volume = (gain - 130.0f) / (200 - 130.0f);
        osc_send_volume(volume);
        usleep(5000);
        // printf("Gain: %d\tVolume: %.2lf\n", gain, volume);
    }
    return NULL;
}

int main() {
    int fd = open(KEYBOARD_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        return EXIT_FAILURE;
    }
    osc_init();

    pthread_t thread;
    pthread_create(&thread, NULL, pressure_loop, NULL);

    struct input_event ev;
    double volume = 0;
    printf("base volume: %.2lf\n", volume);

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            handle_input_event(ev.code, ev.value);

            int pressed_count = count_pressed_keys();
            int idx = get_note_index(keys_pressed, pressed_count);

            if (idx >= 0) {
                osc_send_note(idx);
                printf("Playing %s\tAt %f Hz\tVolume: %.2f\n", 
                    get_note_name(idx), 
                    get_note_frequency(idx), 
                    volume);
            }
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}
