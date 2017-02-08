#include<xinu.h>
#include<stdio.h>

void printsegaddr() {
    kprintf("start addr of text: 0x%08X\n", (uint32)&text);
    kprintf("start addr of data: 0x%08X\n", (uint32)&data);
    kprintf("start addr of bss: 0x%08X\n", (uint32)&bss);
    kprintf("end addr of bss: 0x%08X\n", (uint32)&ebss);
    kprintf("start of text: 0x%08X\n", (uint32)text);
    kprintf("start of data: 0x%08X\n", (uint32)data);
    kprintf("start of bss: 0x%08X\n", (uint32)bss);
    kprintf("following the end of bss: 0x%08X\n", (uint32)ebss);
    kprintf("length of text: %10d\n", (uint32)&etext - (uint32)&text);
    kprintf("length of data: %10d\n", (uint32)&edata - (uint32)&data);
    kprintf("length of bss: %10d\n", (uint32)&ebss - (uint32)&bss);
}
