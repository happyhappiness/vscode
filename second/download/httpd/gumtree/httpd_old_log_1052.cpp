fprintf(stderr, "%s: password too long (>%" APR_SIZE_T_FMT ")\n",
	        argv[0], sizeof(password) - 1);