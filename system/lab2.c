#include <xinu.h>
#include <stdio.h>
#include <lab2.h>

char app1() {
    char res;
    
    uint32 addr=0, cont=0, sav_esp=0;
    asm("movl %%esp, %0\n\tmovl (%%esp), %1" : "=r" (addr), "=r" (cont) );
    sav_esp = (uint32) (&proctab[getpid()])->prstkptr;
    kprintf("before calling func1(): esp addr: 0x%08X, content: 0x%08X, saved ESP: 0x%08X\n", addr, cont, sav_esp);
    
    res = (char) func1(65);
    
    asm volatile("movl %%esp, %0\n\tmovl (%%esp), %1" : "=r" (addr), "=r" (cont) );
    kprintf("after func1() return: esp addr: 0x%08X, content: 0x%08X\n", addr, cont);
    
    return res;
}

int func1(int a) {
    int res;
    res = a + 1;
    
    uint32 addr=0, cont=0;
    asm("movl %%esp, %0\n\tmovl (%%esp), %1" : "=r" (addr), "=r" (cont) );
    kprintf("before func1() return: esp addr: 0x%08X, content: 0x%08X\n", addr, cont);
    
    return res;
}

void looper( int val ) {
    int count = 1;
    while (count < 20) {
        kprintf("%d,%d\n",val,count++);
    }
}
