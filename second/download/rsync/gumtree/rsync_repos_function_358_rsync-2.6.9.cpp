static void send_directory(int f, struct file_list *flist,
			   char *fbuf, int len)
{
	struct dirent *di;
	unsigned remainder;
	char *p;
	DIR *d;
	int start = flist->count;

	if (!(d = opendir(fbuf))) {
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR, errno, "opendir %s failed", full_fname(fbuf));
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
			rprintf(FINFO,
				"cannot send long-named file %s\n",
				full_fname(fbuf));
			continue;
		}

		send_file_name(f, flist, fbuf, NULL, 0);
	}

	fbuf[len] = '\0';

	if (errno) {
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR, errno, "readdir(%s)", full_fname(fbuf));
	}

	closedir(d);

	if (recurse) {
		int i, end = flist->count - 1;
		for (i = start; i <= end; i++)
			send_if_directory(f, flist, flist->files[i], fbuf, len);
	}
}