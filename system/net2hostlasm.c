long net2hostlasm(long x) {
    long res;
    asm("movl    %1, %%edx\n\t"
        "movl    %%edx, %%eax\n\t"
        "andl    $0x000000ff, %%eax\n\t"
        "shll    $24, %%eax\n\t"
        "movl    %%edx, %%ecx\n\t"
        "andl    $0x0000ff00, %%ecx\n\t"
        "shll    $8, %%ecx\n\t"
        "orl     %%ecx, %%eax\n\t"
        "movl    %%edx, %%ecx\n\t"
        "andl    $0x00ff0000, %%ecx\n\t"
        "shrl    $8, %%ecx\n\t"
        "orl     %%ecx, %%eax\n\t"
        "movl    %%edx, %%ecx\n\t"
        "andl    $0xff000000, %%ecx\n\t"
        "shrl    $24, %%ecx\n\t"
        "orl     %%ecx, %%eax\n\t"
        "movl    %%eax, %0"
        : "=r" (res)
        : "r" (x));
    return res;
}
