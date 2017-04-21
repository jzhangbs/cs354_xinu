#include <xinu.h>

pid32 waitchld() {
	intmask mask = disable();
	struct procent *prptr = &proctab[currpid];
	
	prptr->prstate = PR_WAITFORCHLD;
	resched();
	
	restore(mask);
	return prptr->termchldpid;
}
