static void send_directory(int f, struct file_list *flist, char *dir)
{
	DIR *d;
	struct dirent *di;
	char fname[MAXPATHLEN];
	int l;
	char *p;

	d = opendir(dir);
	if (!d) {
		io_error |= IOERR_GENERAL;
		rprintf(FERROR, "opendir %s failed: %s\n",
			full_fname(dir), strerror(errno));
		return;
	}

	strlcpy(fname, dir, MAXPATHLEN);
	l = strlen(fname);
	if (fname[l - 1] != '/') {
		if (l == MAXPATHLEN - 1) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR, "skipping long-named directory: %s\n",
				full_fname(fname));
			closedir(d);
			return;
		}
		strlcat(fname, "/", MAXPATHLEN);
		l++;
	}
	p = fname + strlen(fname);

	local_exclude_list = NULL;

	if (cvs_exclude) {
		if (strlen(fname) + strlen(".cvsignore") <= MAXPATHLEN - 1) {
			strcpy(p, ".cvsignore");
			add_exclude_file(&exclude_list,fname,MISSING_OK,ADD_EXCLUDE);
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
		strlcpy(p, dname, MAXPATHLEN - l);
		send_file_name(f, flist, fname, recurse, 0);
	}
	if (errno) {
		io_error |= IOERR_GENERAL;
		rprintf(FERROR, "readdir(%s): (%d) %s\n",
		    dir, errno, strerror(errno));
	}

	if (local_exclude_list)
		free_exclude_list(&local_exclude_list); /* Zeros pointer too */

	closedir(d);
}