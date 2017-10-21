		rprintf(FINFO,"building file list ... ");
		rflush(FINFO);
	}

	start_write = stats.total_written;

	flist = flist_new();

	if (f != -1) {
		io_start_buffering(f);
	}

	for (i=0;i<argc;i++) {
