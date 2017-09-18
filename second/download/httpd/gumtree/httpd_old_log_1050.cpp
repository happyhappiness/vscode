fprintf(stderr, "%s: username too long (>%" APR_SIZE_T_FMT ")\n",
	        argv[0], sizeof(user) - 1);