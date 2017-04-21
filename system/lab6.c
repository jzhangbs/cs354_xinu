#include <xinu.h>

int32 msg_recv_cb() {
	umsg32 msg = receive();
	kprintf("rcv %d: receice %d\n", currpid, msg);
	return OK;
}

process rcv1() {
	kprintf("rcv %d: reg callback\n",currpid);
	if (regcallback(&msg_recv_cb) != OK) {
		kprintf("callback function registration failed\n");
		return SYSERR;
	}
	int i,j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 1000000; j++);
		kprintf("rcv %d: Running other tasks\n",currpid);
	}
	return OK;
}

process snd1(pid32 rcv){
	int i,j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 1000000; j++);
		kprintf("snd %d: send %d\n", currpid, i);
		send(rcv, (umsg32)(i));
	}
	return OK;
}

process snd2(pid32 rcv, umsg32 msg) {
	int i, j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 1000000; j++);
		kprintf("snd %d: send %d\n", currpid, msg);
		send(rcv, msg);
	}
	return OK;
}

process rcv2() {
	kprintf("rcv %d: reg callback\n",currpid);
	if (regcallbacksig(&msg_recv_cb, XINUSIGRCV, 0) != OK) {
		kprintf("callback function registration failed\n");
		return SYSERR;
	}
	int i,j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 1000000; j++);
		kprintf("rcv %d: Running other tasks\n",currpid);
	}
	return OK;
}

process snd3(pid32 rcv){
	int i,j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 1000000; j++);
		kprintf("snd %d: send %d\n", currpid, i);
		send(rcv, (umsg32)(i));
	}
	return OK;
}

process snd4(pid32 rcv, umsg32 msg) {
	int i, j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 1000000; j++);
		kprintf("snd %d: send %d\n", currpid, msg);
		send(rcv, msg);
	}
	return OK;
}

int32 xtimecb(){
	kprintf("Wall time exceeded!\n");
	return OK;
}

process xtime() {
	if (regcallbacksig(&xtimecb, XINUSIGXTIME, 500) != OK) {
		kprintf("callback function registration failed\n");
		return SYSERR;
	}
	int i;
	for (i = 0; i < 7; i++) {
		sleepms(100);
		kprintf("wall time: %d\n", timediff(proctab[currpid].prstart, clktimefine));
	}
	return OK;
}

int32 chldcb() {
	kprintf("Child process terminated!\n");
	return OK;
}

process parent() {
	if (regcallbacksig(&chldcb, XINUSIGCHLD, 0) != OK) {
		kprintf("callback function registration failed\n");
		return SYSERR;
	}
	
	kprintf("start child\n");
	resume(create(child, 1024, 1, "child", 0));
	int i;
	for (i = 0; i < 10; i++) {
		kprintf("parent: Running other tasks\n");
		sleepms(10);
	}
	return OK;
}

process child() {
	int i;
	for (i = 0; i < 5; i++) {
		kprintf("child\n");
		sleepms(10);
	}
	kprintf("child terminate\n");
	return OK;
}

process server() {
	int k = 0;
	umsg32 msg;
	for (k = 0;k < 2; k++) {
		kprintf("server: listening\n");
		//while( !proctab[currpid].prhasmsg );
		msg = receive();
		kprintf("server: connect to %d\n", msg);
		resume(create(worker, 1024, 1, "worker", 0));
		kprintf("server: start worker and wait\n");
		pid32 w = waitchld();
		kprintf("server: worker %d finished, send request\n", w);
		send((pid32)msg, 0);
	}
	return OK;
}

process client(pid32 s) {
	kprintf("client %d: connect\n", currpid);
	while( send(s, currpid) == SYSERR );
	kprintf("client %d: connected! wait for response\n", currpid);
	receive();
	kprintf("client %d: get response\n", currpid);
	return OK;
}

process worker() {
	int i, tmp;
	sleepms(100);
	kprintf("worker %d: finish\n", currpid);
	return OK;
}

process memtest() {
	kprintf("getmem 8 at a\n");char *a = getmem(8);
	kprintf("getmem 8 at b\n");char *b = getmem(8);
	kprintf("getmem 32 at c\n");char *c = getmem(32);
	kprintf("getmem 16 at d\n");char *d = getmem(16);
	kprintf("freemem 32 at c\n");freemem(c, 32);

	printmemrec();
	printmem();

	kprintf("process terminate\n");
	return 0;
}
