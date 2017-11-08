static void send_directory(int f, struct file_list *flist, char *dir)
{
	DIR *d;
	struct dirent *di;
	char fname[MAXPATHLEN];
	unsigned int offset;
	char *p;

	d = opendir(dir);
	if (!d) {
		io_error |= IOERR_GENERAL;
		rprintf(FERROR, "opendir %s failed: %s\n",
			full_fname(dir), strerror(errno));
		return;
	}

	offset = strlcpy(fname, dir, MAXPATHLEN);
	p = fname + offset;
	if (offset >= MAXPATHLEN || p[-1] != '/') {
		if (offset >= MAXPATHLEN - 1) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR, "skipping long-named directory: %s\n",
				full_fname(fname));
			closedir(d);
			return;
		}
		*p++ = '/';
		offset++;
	}

	if (cvs_exclude) {
		if (strlcpy(p, ".cvsignore", MAXPATHLEN - offset)
		    < MAXPATHLEN - offset) {
			add_exclude_file(&local_exclude_list, fname,
					 XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
		} else {
			io_error |= IOERR_GENERAL;
			rprintf(FINFO,
				"cannot cvs-exclude in long-named directory %s\n",
				full_fname(fname));
		}
	}

	for (errno = 0, di = readdir(d); di; errno = 0, di = readdir(d)) {
		char *dname = d_name(di);
		if (dname[0] == '.' && (dname[1] == '\0'
		    || (dname[1] == '.' && dname[2] == '\0')))
			continue;
		if (strlcpy(p, dname, MAXPATHLEN - offset) < MAXPATHLEN - offset)
			send_file_name(f, flist, fname, recurse, 0);
		else {
			io_error |= IOERR_GENERAL;
			rprintf(FINFO,
				"cannot send long-named file %s\n",
				full_fname(fname));
		}
	}
	if (errno) {
		io_error |= IOERR_GENERAL;
		rprintf(FERROR, "readdir(%s): (%d) %s\n",
			dir, errno, strerror(errno));
	}

	closedir(d);
}