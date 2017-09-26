	if (bar != NULL)
	    printf("%s %s\n", hoststring, bar + 1);
	else
	    puts(hoststring);
    }

#if defined(WIN32) || (defined(NETWARE) && defined(USE_WINSOCK))
     WSACleanup();
#endif

    if (statfile != NULL) {
	FILE *fp;
	fp = fopen(statfile, "w");
