#include<xinu.h>
#include<stdio.h>
#include<lab1.h>

process main();

/* The following part is for lab1 */

process new_proc(void) {
	kprintf("\nLab1 new process\n");
	kprintf("\nCreate child process running forever0()\n");

	pid32 forever0_pid = create(forever0, 1024, 20, "forever0", 0);
	resume(forever0_pid);

	kprintf("\nPID of forever0 is %d\n", (int) forever0_pid);

	kprintf("\nRun main().\n");
	resume(create((void *) main, INITSTK, INITPRIO, "main", 0));

	kprintf("\nSleep for 10 sec.\n");
	sleep(10);

	kprintf("\nKill forever0\n");
	kill(forever0_pid);

	kprintf("\nCheck process table.\n");
	if ( (&proctab[forever0_pid]) -> prstate == PR_FREE )
		kprintf("\nstate of forever0 is PR_FREE\n");
	else
		kprintf("\nstate of forever0 is not PR_FREE\n");

	return OK;
}

process forever0() {
	while(TRUE) {
		putc(CONSOLE, 's');
		sleep(1);
	}

	return OK;
}
