#include<xinu.h>

void stacksmashV() {
    char c = 'V';
    putc(CONSOLE, c);
    /* 
    uint32 ebp, esp;
    asm( "movl %%ebp, %0\n\tmovl %%esp, %1": "=r" (ebp), "=r" (esp) );
    kprintf("V: ebp %08X, esp %08X\n", ebp, esp);
    */
    sleep(1);
    putc(CONSOLE, c);
}
