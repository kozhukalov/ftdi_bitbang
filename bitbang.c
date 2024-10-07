#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bitbang.h>

int deinitialize_ftdi(ftdi_context *ftdi) {
    ftdi_disable_bitbang(ftdi);
    ftdi_usb_close(ftdi);
    ftdi_free(ftdi);
    return 0;
}

int initialize_ftdi(ftdi_context *ftdi) {
    if (ftdi_init(ftdi) < 0) {
        fprintf(stderr, "Failed to initialize libftdi.\n");
        return -1;
    }

    int result = ftdi_usb_open(ftdi, VENDOR, PRODUCT);
    if (result < 0) {
        fprintf(stderr, "Unable to open FTDI device: %s\n", ftdi_get_error_string(ftdi));
        deinitialize_ftdi(ftdi);
        return -1;
    }

    result = ftdi_set_bitmode(ftdi, BIT_MOSI | BIT_MISO | BIT_SCK | BIT_CS, BITMODE_BITBANG);
    if (result < 0) {
        fprintf(stderr, "Failed to set bitmode.\n");
        return -1;
    }
    return 0;
}

void set_cs(ftdi_context *ftdi, int level) {
    unsigned char buf;
    ftdi_read_data(ftdi, &buf, 1);
    if (level)
        buf |= BIT_CS;  // Set high: Deactivate CS
    else
        buf &= ~BIT_CS; // Set low: Activate CS
    ftdi_write_data(ftdi, &buf, 1);
}

unsigned char spi_transfer(ftdi_context *ftdi, unsigned char data) {
    unsigned char bit;
    unsigned char in = 0;
    unsigned char out = 0;
    for (bit = 0x80; bit; bit >>= 1) {
        out = (data & bit) ? BIT_MOSI : 0;
        ftdi_write_data(ftdi, &out, 1);  // Set MOSI
        out |= BIT_SCK;  // Set SCK high
        ftdi_write_data(ftdi, &out, 1);
        ftdi_read_data(ftdi, &in, 1);  // Read MISO
        out &= ~BIT_SCK;  // Set SCK low
        ftdi_write_data(ftdi, &out, 1);
        if (in & BIT_MISO)
            data |= bit;
        else
            data &= ~bit;
    }
    return data;
}
