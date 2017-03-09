#ifndef _MINHEAP_H_
#define _MINHEAP_H_

struct hentry {
	int32	key;
	pid32	pid;
};

extern struct hentry rlist[];

status	newheap();
status	heapinsert(pid32, int32);
pid32	heapgethead();
int32	heapminkey();
pid32	heapgetitem(pid32);
void	printheap();

#define NIL (-1)

#endif
