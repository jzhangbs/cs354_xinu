#include<xinu.h>

void stacksmashV() {
    char c = 'V';
    putc(CONSOLE, c);
    sleepms(200);
    putc(CONSOLE, c);
}
