#include <stdint.h>
#include <stdbool.h>
#include "n64sys.h"
#include "cop0.h"
#include "minidragon.h"

#define DEBUG 1
#include "debug.h"

register uint32_t s3_register asm ("s3");
register uint32_t s4_register asm ("s4");
register uint32_t s5_register asm ("s5");
register uint32_t s6_register asm ("s6");
register uint32_t s7_register asm ("s7");

#include "rdram.c"

__attribute__((noinline, noreturn, noclone, section(".boot")))
void _start(void)
{
    dragon_init();

    //*(volatile uint32_t*)0xbfc007fc = 8;

    usb_init();
    debugf("Libdragon IPL3");
    debugf("C0_STATUS: ", C0_STATUS());
    
    C0_WRITE_CR(0);
    C0_WRITE_COUNT(0);
    C0_WRITE_COMPARE(0);

    debugf("rdram_init()");
    rdram_init();

    debugf("END");
    while(1) {}
}
