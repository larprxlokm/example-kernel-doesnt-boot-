#include <stdint.h>
#include "kbd-driver.c"
#include "kmf-driver.c"

void kernel_main() {
    mouse_init();
    register_keyboard_callback(0); 
    while (1) {
    }
}


// you need to add your own logic here i didnt cause im bad at coding
