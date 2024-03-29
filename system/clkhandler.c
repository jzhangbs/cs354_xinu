/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Increment tick counter */
	if (clktimefine == 0xFFFFFFFF) clktimefine = 0;
	else ++clktimefine;


	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		if (clktime == 0xFFFFFFFF) clktime = 0;
		else clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
	
	struct procent *prptr = &proctab[currpid];
	if (currpid != 0 && timediff(prptr->prstart, clktimefine) > prptr->wall) {
		prptr->sflag[XINUSIGXTIME-SIGOFFSET] = TRUE;
		prptr->wall = 0xffffffff;
	}
}

uint32 timediff(uint32 s, uint32 t) {
	if (s>t) return (0xFFFFFFFF-s) + (t);
	else return t-s;
}
