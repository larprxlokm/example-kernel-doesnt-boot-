.global _start
.extern kernel_main

.text
.align 4
.long 0x1BADB002            /* Magic */
.long 0x00                  /* Flags */
.long -(0x1BADB002 + 0x00)  /* Checksum */

_start:
    mov $stack_top, %esp
    call kernel_main
    cli
1:  hlt
    jmp 1b

.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:
