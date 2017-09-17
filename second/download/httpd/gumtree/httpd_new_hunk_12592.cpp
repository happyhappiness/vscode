    char *szLogRoot;

    if (argc != 3) {
	fprintf(stderr,
		"%s <logfile> <rotation time in seconds>\n\n",
		argv[0]);
#ifdef OS2
	fprintf(stderr,
		"Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
		argv[0]);
#else
	fprintf(stderr,
		"Add this:\n\nTransferLog \"|%s /some/where 86400\"\n\n",
++ apache_1.3.2/src/support/suexec.c	1998-09-17 04:51:08.000000000 +0800
