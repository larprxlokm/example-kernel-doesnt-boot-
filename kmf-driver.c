#include <stdint.h>

#define MOUSE_PORT_DATA 0x60
#define MOUSE_PORT_STATUS 0x64
#define MOUSE_CMD_WAIT 0x64
#define MOUSE_CMD_WRITE 0x60

typedef struct {
    int8_t x_offset;
    int8_t y_offset;
    uint8_t buttons;
} mouse_packet_t;

extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t val);

static void mouse_wait(uint8_t type) {
    if (type == 0) {
        while ((inb(MOUSE_PORT_STATUS) & 1) == 0);
    } else {
        while ((inb(MOUSE_PORT_STATUS) & 2) != 0);
    }
}

static void mouse_write(uint8_t val) {
    mouse_wait(1);
    outb(MOUSE_PORT_STATUS, 0xD4);
    mouse_wait(1);
    outb(MOUSE_PORT_DATA, val);
}

void mouse_init() {
    mouse_wait(1);
    outb(MOUSE_PORT_STATUS, 0xA8);

    mouse_wait(1);
    outb(MOUSE_PORT_STATUS, 0x20);
    mouse_wait(0);
    uint8_t status = inb(MOUSE_PORT_DATA) | 2;
    mouse_wait(1);
    outb(MOUSE_PORT_STATUS, 0x60);
    mouse_wait(1);
    outb(MOUSE_PORT_DATA, status);

    mouse_write(0xF6);
    inb(MOUSE_PORT_DATA);
    mouse_write(0xF4);
    inb(MOUSE_PORT_DATA);
}

mouse_packet_t mouse_decode(uint8_t b0, uint8_t b1, uint8_t b2) {
    mouse_packet_t packet;
    packet.buttons = b0 & 0x07;
    packet.x_offset = (b0 & 0x10) ? (b1 - 256) : b1;
    packet.y_offset = (b0 & 0x20) ? (b2 - 256) : b2;
    return packet;
}
