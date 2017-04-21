#include <xinu.h>
/*
void cbenq( int (* func) (void) e ) {
	struct proctab *prptr = &proctab[currpid];
	prptr->cbq[ prptr->cbe ] = e;
	cbe = (cbe + 1) % NCB;
}

int (* func) (void) cbdeq() {
	struct proctab *prptr = &proctab[currpid];
	int (* func) (void) ret = prptr->cbq[ prptr->cbs ];
	cbs = (cbs + 1) % NCB;
	return ret;
}

inline char isfull() {
	return (proctab[currpid].cbe==proctab[currpid].cbs-1);
}

inline char isempty() {
	return (proctab[currpid].cbe==proctab[currpid].cbs);
}
*/
syscall regcallback( int (* callback) (void) ) {
	intmask mask = disable();
	proctab[currpid].cb = callback;
	restore(mask);
	return OK;
}
