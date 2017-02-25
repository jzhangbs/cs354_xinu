/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

#include<lab2.h>
#include<lab3.h>

#define NSH

pid32 victimpid;

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
	/* //lab2
	recvclr();
	
	kprintf("\ntest net2hostl\n");
	kprintf("net2hostl: 0x%08x\n", net2hostl(0x78563412));
    kprintf("net2hostgcc: 0x%08x\n", net2hostlgcc(0x78563412));
    kprintf("net2hostasm: 0x%08x\n", net2hostlasm(0x78563412));
    
    kprintf("\nprint segment info\n");
    printsegaddr();
	
	kprintf("\nrun app1\n");
    
    uint32 addr=0, cont=0, sav_esp=0;
    pid32 pid = getpid();
    asm("movl %%esp, %0\n\tmovl (%%esp), %1" : "=r" (addr), "=r" (cont) );
    sav_esp = (uint32) (&proctab[pid])->prstkptr;
    kprintf("before creating app1: esp addr: 0x%08X, content: 0x%08X, saved ESP: 0x%08X\n", addr, cont, sav_esp);
    
    pid32 app1_pid = create(app1, 1024, 20, "app1", 0);
    
    asm("movl %%esp, %0\n\tmovl (%%esp), %1" : "=r" (addr), "=r" (cont) );
    sav_esp = (uint32) (&proctab[pid])->prstkptr;
    kprintf("before resuming app1: esp addr: 0x%08X, content: 0x%08X, saved ESP: 0x%08X\n", addr, cont, sav_esp);
    
    resume(app1_pid);
    
    sleep(1);
    
    kprintf("\ncreate 3 looper process\n");
    pid32 looper1, looper2, looper3;
    looper1 = create(looper, 512, 10, "looper1", 1, 100);
    looper2 = create(looper, 512, 10, "looper2", 1, 200);
    looper3 = create(looper, 512, 30, "looper3", 1, 300);
    
    kprintf("main\n");
    resume(looper1);
    kprintf("main\n");
    resume(looper2);
    kprintf("main\n");
    resume(looper3);
    sleepms(3);
    
    int i = 0;
    for (i = 0; i < 10; i++) {
        kprintf("MAIN\n");
        sleepms(3);
    }
*/ 
    /* 
    sleep(3);
    kprintf("looper1: %x, looper2: %x, looper3: %x, main: %x\n", 
    	(&proctab[looper1])->prcpuused,
	(&proctab[looper2])->prcpuused,
	(&proctab[looper3])->prcpuused,
	(&proctab[getpid()])->prcpuused);
    */
    
    //rcreate(stacksmashA, 1024, 10, "stacksmashA", 0);
    //rcreate(stacksmashV, 1024, 20, "stacksmashV", 0);
    //sleep(5);
    // end lab2
/* lab3
    resched_cntl(DEFER_START);
    rcreate(iobnd, 1024, 1, "cpubnd1", 0);
    rcreate(iobnd, 1024, 1, "cpubnd2", 0);
    rcreate(cpubnd, 1024, 1, "cpubnd3", 0);
    rcreate(cpubnd, 1024, 1, "cpubnd4", 0);
    resched_cntl(DEFER_STOP);
*/
    rcreate(stacksmashA, 1024, 1, "stacksmashA", 0);
    victimpid = create(stacksmashV, 1024, 1, "stacksmashV", 0);
    resume(victimpid);
	
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

