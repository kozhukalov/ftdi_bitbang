#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/bitbang.h"


int main(int argc, char **argv) {

    ftdi_context *ftdi = (ftdi_context *)malloc(sizeof(ftdi_context));
    unsigned char data = 0xA5;  // 10100101

    if (initialize_ftdi(ftdi) < 0) {
        return EXIT_FAILURE;
    }

    set_cs(ftdi, 0);  // Activate slave device
    unsigned char received = spi_transfer(ftdi, data);
    printf("Received: 0x%02X\n", received);
    set_cs(ftdi, 1);  // Deactivate slave device

    deinitialize_ftdi(ftdi);
    return EXIT_SUCCESS;
}
