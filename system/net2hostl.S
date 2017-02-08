    .text
	.globl	net2hostl
	.type	net2hostl, @function

net2hostl:
    
    pushl   %ebp
    movl    %esp, %ebp

    movl    8(%ebp), %edx
    movl    %edx, %eax
    andl    $0x000000ff, %eax
    shll    $24, %eax
    movl    %edx, %ecx
    andl    $0x0000ff00, %ecx
    shll    $8, %ecx
    orl     %ecx, %eax
    movl    %edx, %ecx
    andl    $0x00ff0000, %ecx
    shrl    $8, %ecx
    orl     %ecx, %eax
    movl    %edx, %ecx
    andl    $0xff000000, %ecx
    shrl    $24, %ecx
    orl     %ecx, %eax
    popl    %ebp
    ret
