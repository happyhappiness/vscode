static void send_directory(int f, struct file_list *flist, char *fbuf, int len,
			   int flags)
{
	struct dirent *di;
	unsigned remainder;
	char *p;
	DIR *d;
	int divert_dirs = (flags & FLAG_DIVERT_DIRS) != 0;
	int start = flist->used;
	int filter_level = f == -2 ? SERVER_FILTERS : ALL_FILTERS;

	assert(flist != NULL);

	if (!(d = opendir(fbuf))) {
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR_XFER, errno, "opendir %s failed", full_fname(fbuf));
		return;
	}

	p = fbuf + len;
	if (len != 1 || *fbuf != '/')
		*p++ = '/';
	*p = '\0';
	remainder = MAXPATHLEN - (p - fbuf);

	for (errno = 0, di = readdir(d); di; errno = 0, di = readdir(d)) {
		char *dname = d_name(di);
		if (dname[0] == '.' && (dname[1] == '\0'
		    || (dname[1] == '.' && dname[2] == '\0')))
			continue;
		if (strlcpy(p, dname, remainder) >= remainder) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR_XFER,
				"cannot send long-named file %s\n",
				full_fname(fbuf));
			continue;
		}
		if (dname[0] == '\0') {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR_XFER,
				"cannot send file with empty name in %s\n",
				full_fname(fbuf));
			continue;
		}

		send_file_name(f, flist, fbuf, NULL, flags, filter_level);
	}

	fbuf[len] = '\0';

	if (errno) {
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR_XFER, errno, "readdir(%s)", full_fname(fbuf));
	}

	closedir(d);

	if (f >= 0 && recurse && !divert_dirs) {
		int i, end = flist->used - 1;
		/* send_if_directory() bumps flist->used, so use "end". */
		for (i = start; i <= end; i++)
			send_if_directory(f, flist, flist->files[i], fbuf, len, flags);
	}
}