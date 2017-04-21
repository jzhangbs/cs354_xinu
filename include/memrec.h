typedef struct memrec{
	uint32 addr, len;
} memrec;

#define NMEM 20

syscall memadd(memrec);
syscall memsub(memrec);
syscall printmemrec();
syscall printmem();
