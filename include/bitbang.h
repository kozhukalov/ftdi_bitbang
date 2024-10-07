#include <ftdi.h>

#ifndef __BITBANG_H
#define __BITBANG_H

#ifdef __cplusplus
extern "C" {
#endif

#define VENDOR 0x0403  // FTDI
#define PRODUCT 0x6001  // FT245RL
#define BIT_SCK 0x01  // D0
#define BIT_MOSI 0x02  // D1
#define BIT_CS 0x04  // D2
#define BIT_MISO 0x08  // D3

typedef struct ftdi_context ftdi_context;

int deinitialize_ftdi(ftdi_context *ftdi);
int initialize_ftdi(ftdi_context *ftdi);
void set_cs(ftdi_context *ftdi, int level);
unsigned char spi_transfer(ftdi_context *ftdi, unsigned char data);

#ifdef __cplusplus
}
#endif

#endif  // __BITBANG_H
