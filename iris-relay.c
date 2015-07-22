#include <stdio.h>
#include <ftdi.h>
#include <string.h>

#define PIN 0x01  /* TX */

void print_usage() {
    puts("iris-relay: on|off|reset");
}

void set_pin(struct ftdi_context *ftdic, unsigned char value) {
    unsigned char c = value ? PIN : 0x0;
    ftdi_write_data(ftdic, &c, 1);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        print_usage();
        return 1;
    }

    struct ftdi_context ftdic;

    ftdi_init(&ftdic);

    if(ftdi_usb_open(&ftdic, 0x0403, 0x6001) < 0) {
        puts("Can't open device");
        return 1;
    }

    ftdi_set_bitmode(&ftdic, PIN, BITMODE_BITBANG); 

    if (!strcmp(argv[1], "on")) {
        set_pin(&ftdic, 1);
    } else if (!strcmp(argv[1], "off")) {
        set_pin(&ftdic, 0);
    } else if (!strcmp(argv[1], "reset")) {
        set_pin(&ftdic, 0);
        sleep(1);
        set_pin(&ftdic, 1);
    } else {
        print_usage();
        return 1;
    }

    return 0;
}

