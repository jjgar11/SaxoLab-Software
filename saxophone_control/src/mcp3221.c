#include "osc_handler.h"
#include "mcp3221.h"
#include "constants.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>

static int i2c_fd = -1;

static int reopen_i2c() {
    if (i2c_fd != -1) {
        close(i2c_fd);
        i2c_fd = -1;
    }

    // Open the I2C device
    i2c_fd = open(MOUTHPIECE, O_RDWR);
    if (i2c_fd < 0) {
        perror("Failed to open mouthpiece sensor");
        return -1;
    }

    // Set the I2C slave address
    if (ioctl(i2c_fd, I2C_SLAVE, MCP3221_ADDR) < 0) {
        perror("Failed to set slave address");
        close(i2c_fd);
        i2c_fd = -1;
        return -1;
    }

    return 0;
}

static int mouthpiece_gain(void) {
    if (i2c_fd < 0 && reopen_i2c() < 0)
        return -1;

    // Read data from the specified register
    unsigned char data[2];
    ssize_t r = read(i2c_fd, data, 2);
    if (r != 2) {
        perror("Failed to read data, retrying...");
        if (reopen_i2c() < 0)
            return -1;
        r = read(i2c_fd, data, 2);
        if (r != 2) {
            perror("Second read failed");
            return -1;
        }
    }

    int gain = ((data[0] << 8) | data[1]) >> 4;
    return gain;
}

void* pressure_loop(void* arg) {
    while (1) {
        int gain = mouthpiece_gain();
        double volume = (gain - 130.0f) / (200 - 130.0f);
        osc_send_volume(volume);
        usleep(5000);
    }
    return NULL;
}
