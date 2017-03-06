#include<xinu.h> 

uint8 mainStarted = 0;

void inline printTime() {
 int pit;
    kprintf("(clktimefine: %d, tcu: %d, trp: %d)\n", clktimefine, total_cpu_usage, total_ready_proc);
    for (pit=1; pit<NPROC; pit++) {
    	if (proctab[pit].prstate == PR_READY || proctab[pit].prstate == PR_CURR)
	    kprintf("(pid: %d, time: %d, name: %s)\n",pit, proctab[pit].prcpuused, proctab[pit].prname);
    }
}
