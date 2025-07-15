#include "mcp3221.h"
#include "constants.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>

int mouthpiece_gain(void) {

    // Open the I2C device
    int file = open(MOUTHPIECE, O_RDWR);
    if (file < 0) {
        perror("Failed to open mouthpiece sensor");
        return -1;
    }

    // Set the I2C slave address
    if (ioctl(file, I2C_SLAVE, MCP3221_ADDR) < 0) {
        perror("Failed to set slave address");
        close(file);
        return -1;
    }

    // Read data from the specified register
    unsigned char data[2];
    ssize_t r = read(file, data, 2);
    close(file);

    if (r != 2) {
        perror("Failed to read data");
        return -1;
    }

    int gain = ((data[0] << 8) | data[1]) >> 4;
    printf("Data read from device 0x%02X: 0x%02X \n", MCP3221_ADDR, gain);
    return gain;
}
