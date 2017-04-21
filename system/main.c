/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

#define NSH

process	main(void)
{
	kprintf("\nHello World!\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
	
	// Add name and ID to welcome message.
	kprintf("\n*******************************************\n");
	kprintf(  "*         Jingyang ZHANG zhan2744         *\n");
	kprintf(  "*******************************************\n");
	
	kprintf("\n...creating a shell\n");
	//lab3 
	/*
    	kprintf("\ntest fair scheduling\n");
    	resched_cntl(DEFER_START);
    	rcreate(cpubnd, 1024, 1, "cpubnd1", 0);
    	rcreate(cpubnd, 1024, 1, "cpubnd2", 0);
    	rcreate(cpubnd, 1024, 1, "cpubnd3", 0);
    	rcreate(cpubnd, 1024, 1, "cpubnd4", 0);
    	resched_cntl(DEFER_STOP);*/
	
	pid32 rcv;

	kprintf("\nSingle rcv, single snd\n");
	resched_cntl(DEFER_START);
	resume(rcv=create(rcv1, 1024, 1, "rcv1", 0));
	resume(create(snd1, 1024, 1, "snd1", 1, rcv));
	resched_cntl(DEFER_STOP);
	
	sleep(2);
	kprintf("\nSingle rcv, multiple snd\n");
	
	resched_cntl(DEFER_START);
	resume(rcv=create(rcv1, 1024, 1, "rcv1", 0));
	resume(create(snd2, 1024, 1, "snd2", 2, rcv, 0));
	resume(create(snd2, 1024, 1, "snd2", 2, rcv, 1));
	resume(create(snd2, 1024, 1, "snd2", 2, rcv, 2));
	resume(create(snd2, 1024, 1, "snd2", 2, rcv, 3));
	resched_cntl(DEFER_STOP);
	
	sleep(2);
	
	kprintf("\nSIGNAL Single rcv, single snd\n");
	resched_cntl(DEFER_START);
	resume(rcv=create(rcv2, 1024, 1, "rcv2", 0));
	resume(create(snd3, 1024, 1, "snd3", 1, rcv));
	resched_cntl(DEFER_STOP);
	
	sleep(2);
	kprintf("\nSIGNAL Single rcv, multiple snd\n");
	
	resched_cntl(DEFER_START);
	resume(rcv=create(rcv2, 1024, 1, "rcv2", 0));
	resume(create(snd4, 1024, 1, "snd4", 2, rcv, 0));
	resume(create(snd4, 1024, 1, "snd4", 2, rcv, 1));
	resume(create(snd4, 1024, 1, "snd4", 2, rcv, 2));
	resume(create(snd4, 1024, 1, "snd4", 2, rcv, 3));
	resched_cntl(DEFER_STOP);
	
	sleep(2);
	kprintf("\nSIGNAL Wall time\n");
	
	resume(create(xtime, 1024, 1, "xtime", 0));
	
	sleep(2);
	kprintf("\nSIGNAL child\n");
	
	resume(create(parent, 1024, 1, "parent", 0));
	
	sleep(2);
	kprintf("\nServer/client\n");
	
	resched_cntl(DEFER_START);
	resume(rcv=create(server, 1024, 1, "server", 0));
	resume(create(client, 1024, 1, "client", 1, rcv));
	resume(create(client, 1024, 1, "client", 1, rcv));
	resched_cntl(DEFER_STOP);

	sleep(2);
	kprintf("\nTest garbage collection\n");

	printmem();
	
	resume(create(memtest, 1024, 1, "memtest", 0));

	printmem();

#ifndef NSH	
	pid32 shell_pid = create(shell, 8192, 50, "shell", 1, CONSOLE);
	resume(shell_pid);

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		if ((&proctab[shell_pid])->prstate != PR_FREE) continue;
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
#endif
	return OK;
}

