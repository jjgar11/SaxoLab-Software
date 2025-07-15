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
    double volume = 0;
    printf("base volume: %.2lf\n", volume);

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            handle_input_event(ev.code, ev.value);

            int pressed_count = count_pressed_keys();
            int idx = get_note_index(keys_pressed, pressed_count);

            if (idx >= 0) {
                int gain = mouthpiece_gain();
                usleep(50000);
                volume = (gain - 130.0f) / (250 - 130.0f);
                osc_send_volume(volume);
                printf("Gain: %d\tVolume: %.2lf\n", gain, volume);

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
