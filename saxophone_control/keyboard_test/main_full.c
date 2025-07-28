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

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            handle_input_event(ev.code, ev.value);

            int idx = get_note_index(keys_pressed);

            if (idx >= 0) {
                osc_send_note(idx);
                printf("Playing %s\tAt %f Hz\n", 
                    get_note_name(idx), 
                    get_note_frequency(idx));
            }
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}
