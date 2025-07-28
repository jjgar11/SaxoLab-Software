#include "audio.h"
#include "osc_handler.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

pid_t faust_pid = -1;

void start_faust() {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/root/faust/sax_full/compiled_programs/sax_synth_hslider", 
              "sax_synth_hslider", "-port", "5513", NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        faust_pid = pid;
        printf("Faust iniciado con PID: %d\n", faust_pid);
    } else {
        perror("fork failed");
    }
    osc_init();
}

void stop_faust() {
    if (faust_pid > 0) {
        kill(faust_pid, SIGTERM);
        printf("Faust detenido (PID %d)\n", faust_pid);
        faust_pid = -1;
    }
}

void play_mp3(const char* filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s%s", AUDIO_PREFIX, filename, AUDIO_EXT);
    printf("Reproduciendo %s\n", filepath);

    char command[300];
    snprintf(command, sizeof(command), "ffplay -nodisp -autoexit -loglevel quiet \"%s\"", filepath);

    system(command);
}
