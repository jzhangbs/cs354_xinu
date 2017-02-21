
#include <xinu.h>

#define LOOP1 20
#define LOOP2 100

void iobnd() {
    int i,j;
    for (i=0; i<LOOP1; i++) {
        for (j=0; j<LOOP2; j++) {
	    sleepms(1);
	}
	kprintf("(iobnd:%d,%d,%d,%d)\n", currpid, i, proctab[currpid].prcpuused, preempt);
    }
    kprintf("(iobnd:%d,%d)\n",currpid, proctab[currpid].prcpuused);

}
