	if (human_readable > 1 && argc == 2 && !am_server) {
		/* Allow the old meaning of 'h' (--help) on its own. */
		usage(FINFO);
		exit_cleanup(0);
	}

#ifdef HAVE_SETVBUF
	if (outbuf_mode && !am_server) {
		int mode = *(uchar *)outbuf_mode;
		if (islower(mode))
			mode = toupper(mode);
		fflush(stdout); /* Just in case... */
