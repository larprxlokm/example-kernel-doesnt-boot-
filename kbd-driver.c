#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

typedef void (*key_callback_t)(uint8_t scancode);

static key_callback_t key_handler = 0;

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void keyboard_handler_main() {
    uint8_t status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        uint8_t scancode = inb(KEYBOARD_DATA_PORT);
        if (key_handler) {
            key_handler(scancode);
        }
    }
    outb(0x20, 0x20);
}

void register_keyboard_callback(key_callback_t handler) {
    key_handler = handler;
}
