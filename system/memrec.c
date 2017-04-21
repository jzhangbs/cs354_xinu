#include <xinu.h>

syscall memadd(memrec m) {
	int i;
	int adjhead = -1, adjtail = -1;
	struct procent *prptr = &proctab[currpid];
	//kprintf("add addr: %d, len: %d\n",m.addr, m.len);
	for (i = 0; i < prptr->memtop; i++) {
		if ( prptr->prmem[i].addr + prptr->prmem[i].len == m.addr ) {
			adjtail = i;
		}
		if ( prptr->prmem[i].addr == m.addr + m.len ) {
			adjhead = i;
		}
	}
	if (adjhead != -1 && adjtail != -1) {
		prptr->prmem[adjtail].len += m.len + prptr->prmem[adjhead].len;
		prptr->prmem[adjhead] = prptr->prmem[prptr->memtop--];
	}
	else if (adjhead != -1) {
		prptr->prmem[adjhead].addr = m.addr;
		prptr->prmem[adjhead].len += m.len;
	}
	else if (adjtail != -1) {
		prptr->prmem[adjtail].len += m.len;
	}
	else {
		if (prptr->memtop == NMEM) return SYSERR;
		prptr->prmem[prptr->memtop++] = m;
	}
	return OK;
}

syscall memsub(memrec m) {
	int i;
	struct procent *prptr = &proctab[currpid];
	//kprintf("sub addr: %d, len: %d\n",m.addr, m.len);
	for (i = 0; i < prptr->memtop; i++) {
		if (prptr->prmem[i].addr == m.addr && prptr->prmem[i].len == m.len) {
			prptr->prmem[i] = prptr->prmem[--prptr->memtop];
			return OK;
		}
		else if (prptr->prmem[i].addr < m.addr && 
				(prptr->prmem[i].addr + prptr->prmem[i].len) > (m.addr + m.len) ) {
			if (prptr->memtop == NMEM) return SYSERR;
			uint32 len2 = (prptr->prmem[i].addr + prptr->prmem[i].len) - (m.addr + m.len);
			memrec newm = {(m.addr+m.len), len2};
			prptr->prmem[i].len = m.addr - prptr->prmem[i].addr;
			prptr->prmem[prptr->memtop++] = newm;
			return OK;
		}
		else if ( prptr->prmem[i].addr < m.addr && (prptr->prmem[i].addr + prptr->prmem[i].len) == (m.addr + m.len)  ) {
			prptr->prmem[i].len = m.addr - prptr->prmem[i].addr;
			return OK;
		}
		else if (  prptr->prmem[i].addr == m.addr && (prptr->prmem[i].addr + prptr->prmem[i].len) > (m.addr + m.len) ) {
			prptr->prmem[i].addr = m.addr + m.len;
			prptr->prmem[i].len -= m.len;
			return OK;
		}
	}
	return SYSERR;
}

syscall printmemrec() {
	int i;
	struct procent *prptr = &proctab[currpid];
	kprintf("memory record:\nlen: %d\n", prptr->memtop);
	for (i = 0; i < prptr->memtop; i++) {
		kprintf("addr: %d, len: %d\n", prptr->prmem[i].addr, prptr->prmem[i].len);
	}
	kprintf("\n");
	return OK;
}

syscall printmem() {
	kprintf("free memory:\n");
	struct memblk *p = &memlist;
	while (p!=NULL) {
		kprintf("addr: %d, len: %d\n", (uint32)p, p->mlength);
		p = p->mnext;
	}
	kprintf("\n");
	return OK;
}
