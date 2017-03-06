#include <xinu.h>

#define LOOP1 150
#define LOOP2 5000000

void cpubnd() {
    int i,j,tmp=0;
    for (i=0; i<LOOP1; i++) {
        for (j=0; j<LOOP2; j++) {
	    tmp+=7;
	    tmp-=7;
	}
	kprintf("(cpubnd:%d,%d,%d,%d)\n", currpid, i, proctab[currpid].prcpuused, preempt);
    }
    kprintf("(cpubnd:%d,%d)\n",currpid, proctab[currpid].prcpuused);

}
