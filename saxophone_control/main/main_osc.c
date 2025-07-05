#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/input_handler.h"
#include "../src/keymap.h"
#include "../src/osc_handler.h"
#include "../src/constants.h"

int main() {
    int fd = open(KEYBOARD_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        return EXIT_FAILURE;
    }
    osc_init();

    struct input_event ev;

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            handle_input_event(ev.code, ev.value);
            int pressed_count = count_pressed_keys();
            int idx = get_note_index(keys_pressed, pressed_count);
            if (idx >= 0) {
                osc_send_note_index(idx);
                osc_send_volume(0.2);
                printf("Playing %s\nPressed keys : %d\n", get_note_name(idx), pressed_count);
            } else {
                osc_send_volume(0.0);
            }
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}
