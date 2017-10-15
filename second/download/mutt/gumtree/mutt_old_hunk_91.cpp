/*
 * C version by Wessel Dankers <wsl@fruit.eu.org>
 *
 * This code is in the public domain.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	char **opts, **opt, *pfx;
	int i;

	opts = malloc((2 * argc + 1) * sizeof (* opts));	/* __MEM_CHECKED__ */
	if(!opts) {
		perror(argv[0]);
		exit(2);
	}

