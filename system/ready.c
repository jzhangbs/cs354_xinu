/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];

	if (pid != 0 && prptr->prstate != PR_CURR)
	    total_cpu_usage += prptr->prcpuused;

	prptr->prstate = PR_READY;	
	heapinsert(pid, prptr->prcpuused);
	resched();

	return OK;
}
