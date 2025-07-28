#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY) {
            handle_input_event(ev.code, ev.value);

            if (is_exit_combination(keys_pressed)) {
                printf("Saliendo del modo libre...\n");
                stop_faust();
                return;
            }

            int idx = get_note_index(keys_pressed);

            if (idx >= 0) {
                osc_send_note(idx);
                printf("Playing %s\tAt %f Hz\n", 
                    get_note_name(idx), 
                    get_note_frequency(idx));
            }
        }
    }
}

void training_mode(int fd) {
    srand(time(NULL));

    struct input_event ev;
    printf("Entrando a modo entrenamiento\n");

    while (1) {
        int target_idx = get_random_note_index();
        float target_freq = get_note_frequency(target_idx);

        char filename[32];
        snprintf(filename, sizeof(filename), "%.2f", target_freq);
        play_audio(filename);

        time_t start = time(NULL);

        clean_keys (keys_pressed);
        start_faust();
        while (1) {

            pthread_t thread;
            pthread_create(&thread, NULL, pressure_loop, NULL);

            if (read(fd, &ev, sizeof(ev)) <= 0) continue;
            if (ev.type != EV_KEY) continue;

            handle_input_event(ev.code, ev.value);

            if (is_exit_combination(keys_pressed)) {
                printf("Saliendo del modo entrenamiento...\n");
                stop_faust();
                return;
            }

            int user_idx = get_note_index(keys_pressed);

            if (user_idx >= 0) {
                osc_send_note(user_idx);
            }

            if (user_idx == target_idx) {
                osc_send_note(target_idx);
                printf("¡Correcto! %s\n", get_note_name(user_idx));
                usleep(1000000);
                stop_faust();
                play_audio("excelente");
                break;
            }

            if (time(NULL) - start >= WAIT_TIMEOUT) {
                stop_faust();
                printf("Reproduciendo de nuevo: %s\n", get_note_name(target_idx));
                play_audio(filename);
                start_faust();
                start = time(NULL);
            }
        }
    }
}