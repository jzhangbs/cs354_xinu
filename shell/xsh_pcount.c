/* xsh_pcount.c - xsh_pcount */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/**
 * xsh_pcount - shell command to print the total number of process. 
 *
 **/

shellcmd xsh_pcount(int nargs, char *args[]) {
	
	/* For argument '--help', emit help about the 'pcount' command */
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tDisplay the total number of process\n");
		printf("Options:\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}

	/* check for valid number of arguments */

	if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",args[0]);
		return 1;
	}

	/* Print the number of process */

	int32 count=0, i;
	struct procent *prptr;
	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		if (prptr->prstate != PR_FREE)
			count++;
	}
	printf("Total number of process: %d\n", count);
	
	return 0;
}
