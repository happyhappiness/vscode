fprintf(stderr, " -d  Force CRYPT encryption of the password"
#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
	    " (default)"
#endif
	    ".\n");