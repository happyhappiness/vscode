
    tn = NULL;
    signal(SIGINT, (void (*)()) interrupted);
    if (argc == 4) {
	if (strcmp(argv[1], "-c"))
	    usage();
      if (!(tfp = fopen(argv[2], "w+"))) {
	    fprintf(stderr, "Could not open passwd file %s for writing.\n",
		    argv[2]);
	    perror("fopen");
	    exit(1);
	}
	printf("Adding password for %s.\n", argv[3]);
