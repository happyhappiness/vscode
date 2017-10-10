		}
		oflags |= O_CREAT;
	}

	logfd = open(logfile, oflags, 0666);
	if (logfd < 0) {
		if (!(oflags & O_CREAT) && errno == ENOENT)
			return 0;

		if ((oflags & O_CREAT) && errno == EISDIR) {
			if (remove_empty_directories(logfile)) {
				int save_errno = errno;
				error("There are still logs under '%s'",
				      logfile);
				errno = save_errno;
				return -1;
