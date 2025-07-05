#include "mcp3221.h"
#include "constants.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>

#define MCP3221_ADDR 0x4D

unsigned char mouthpiece_gain(void) {
    int file;
    unsigned char gain, reg = 0x00;

    // Open the I2C device
    if ((file = open(MOUTHPIECE, O_RDWR)) < 0) {
        perror("Failed to open mouthpiece sensor");
        return 0;
    }

    // Set the I2C slave address
    if (ioctl(file, I2C_SLAVE, MCP3221_ADDR) < 0) {
        perror("Failed to set slave address");
        close(file);
        return 0;
    }

    // Write the register address to read from
    if (write(file, &reg, sizeof(reg)) != sizeof(reg)) {
        perror("Failed to write register address");
        close(file);
        return 0;
    }

    // Read data from the specified register
    if (read(file, &gain, sizeof(gain)) != sizeof(gain)) {
        perror("Failed to read data");
        close(file);
        return 0;
    }

    printf("Data read from device 0x%02X: 0x%02X \n", MCP3221_ADDR, gain);
    close(file);
    return gain;
}
