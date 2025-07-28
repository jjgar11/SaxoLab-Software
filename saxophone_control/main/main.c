#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "./modes.h"
#include "../src/audio.h"
#include "../src/constants.h"


int main() {
    
    int fd = open(KEYBOARD_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        return EXIT_FAILURE;
    }

    struct input_event ev;

    play_mp3("bienvenido");

    while (1)
    {
        play_mp3("menu");
        play_mp3("modo");
        while (read(fd, &ev, sizeof(ev)) > 0) {
            if (ev.type == EV_KEY && ev.value == 1) {
                if (
                    ev.code == 4 || 
                    ev.code == 5 || 
                    ev.code == 6 || 
                    ev.code == 7
                ) {
                    play_mp3("libre");
                    free_mode(fd);
                }
                else if (
                    ev.code == 8 || 
                    ev.code == 9 || 
                    ev.code == 10
                ) {
                    play_mp3("entrenamiento");
                    training_mode(fd);
                }
            }
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}
