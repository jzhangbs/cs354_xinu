/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prcpuused < firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prcpuused);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	
	uint32 add_time = timediff(ptold->prctxswstart, clktimefine);
	uint32 rest = 0xFFFFFFFE - ptold->prcpuused;
	if (rest < add_time) ptold->prcpuused = 0xFFFFFFFE;
	else ptold->prcpuused += add_time;
	ptnew->prctxswstart = clktimefine;
	
	//kprintf("switch %x\n", currpid);
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */
	
	int (* callback) (void);
	if (ptold->cb != NULL && ptold->rcvcount) {
		callback = ptold->cb;
		enable();
		if ( callback() != OK ) {
			kprintf("Callback function error.\n");
		}
		disable();
		ptold->rcvcount=FALSE;
	}
	
	int i;
	for (i = 0; i < SIGNUM; i++) {
		if (ptold->sflag[i] && ptold->cbq[i]!=NULL) {
			enable();
			if ( ptold->cbq[i]() != OK ) {
				kprintf("Callback function error.\n");
			}
			disable();
			ptold->sflag[i]=FALSE;
		}
		if (ptold->sflag[i] && ptold->cbq[i]==NULL)
			ptold->sflag[i]=FALSE;
	}

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
