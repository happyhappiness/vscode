static void send_directory(int f, struct file_list *flist, char *dir)
{
	DIR *d;
	struct dirent *di;
	char fname[MAXPATHLEN];
	int l;
	char *p;

	d = opendir(dir);
	if (!d) {
		io_error = 1;
		rprintf(FERROR, "opendir(%s): %s\n", dir, strerror(errno));
		return;
	}

	strlcpy(fname, dir, MAXPATHLEN);
	l = strlen(fname);
	if (fname[l - 1] != '/') {
		if (l == MAXPATHLEN - 1) {
			io_error = 1;
			rprintf(FERROR,
				"skipping long-named directory %s\n",
				fname);
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
			local_exclude_list =
			    make_exclude_list(fname, NULL, 0, 0);
		} else {
			io_error = 1;
			rprintf(FINFO,
				"cannot cvs-exclude in long-named directory %s\n",
				fname);
		}
	}

	for (di = readdir(d); di; di = readdir(d)) {
		char *dname = d_name(di);
		if (strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0)
			continue;
		strlcpy(p, dname, MAXPATHLEN - l);
		send_file_name(f, flist, fname, recurse, 0);
	}

	if (local_exclude_list) {
		add_exclude_list("!", &local_exclude_list, 0);
	}

	closedir(d);
}