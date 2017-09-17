    char *szLogRoot;

    if (argc != 3) {
	fprintf(stderr,
		"%s <logfile> <rotation time in seconds>\n\n",
		argv[0]);
#ifdef __EMX__
	fprintf(stderr,
		"Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
		argv[0]);
#else
	fprintf(stderr,
		"Add this:\n\nTransferLog \"|%s /some/where 86400\"\n\n",
