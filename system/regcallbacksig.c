#include <xinu.h>

syscall regcallbacksig( int (* func) (void), uint16 ssig, uint32 oparg ) {
	struct procent *prptr = &proctab[currpid];
	prptr->cbq[ssig-SIGOFFSET] = func;
	if (ssig==XINUSIGXTIME) prptr->wall = oparg;
	return OK;
}

