#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

    struct input_event ev;

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            handle_input_event(ev.code, ev.value);
            int pressed_count = count_pressed_keys();
            int idx = get_note_index(keys_pressed, pressed_count);
            if (idx >= 0) {
                unsigned char gain = mouthpiece_gain();
                osc_send_volume((gain - 7) * 5.0f / 8);
                printf("Playing %s\nPressed keys : %d\n", get_note_name(idx), pressed_count);
            }
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}
