#include <xinu.h>

struct hentry rlist[NPROC];
int32 size = 0;

#define	prt(idx)	((idx-1)/2)
#define	left(idx)	(idx*2+1)
#define	right(idx)	(idx*2+2)
#define refresh(idx)	proctab[rlist[idx].pid].rlpos=idx

void sn(int32 a, int32 b) {
	struct hentry tmp = rlist[a];
	rlist[a] = rlist[b];
	rlist[b] = tmp;

	refresh(a);
	refresh(b);
}

void percup(int32 idx) {
	if (idx == 0) return;
	if (rlist[idx].key < rlist[prt(idx)].key)
		sn(idx, prt(idx));
	percup(prt(idx));
}

void percdown(int32 idx) {
	if (left(idx) >= size ) return;

	int r,l;
	l = rlist[left(idx)].key;
	if ( right(idx) >= size )
		r = 0x7FFFFFFF;
	else r = rlist[right(idx)].key;
	if (rlist[idx].key > l || rlist[idx].key > r) {
		if ( l > r ) {
			sn(right(idx),idx);
			percdown(right(idx));
		}
		else {
			sn(left(idx),idx);
			percdown(left(idx));
		}
	}
}

status newheap() {
	size = 0;
	return OK;
}

status heapinsert(pid32 _pid, int32 _key) {
	if (size == NPROC-1) return SYSERR;
	rlist[size].key = _key;
	rlist[size++].pid = _pid;
	proctab[_pid].rlpos = size-1;
	percup(size-1);

	total_ready_proc++;

	return OK;
}

pid32 heapgethead() {
	pid32 head = rlist[0].pid;
	rlist[0] = rlist[--size];

	proctab[head].rlpos = NIL;
	refresh(0);

	percdown(0);

	total_ready_proc--;

	return head;
}

int32 heapminkey() {
	return rlist[0].key;
}

pid32 heapgetitem(pid32 _pid) {
	struct procent pr = proctab[_pid];

	int idx = pr.rlpos;
	if (idx == NIL) return SYSERR;

	rlist[idx] = rlist[--size];
	pr.rlpos = NIL;
	refresh(idx);

	percup(idx);
	percdown(idx);

	total_ready_proc--;

	return _pid;
}

void printheap() {
	int i;
	kprintf("[");
	for (i = 0; i < size; i++)
		kprintf("(%d, %d)", rlist[i].pid, rlist[i].key);
	kprintf("]\n");
}
