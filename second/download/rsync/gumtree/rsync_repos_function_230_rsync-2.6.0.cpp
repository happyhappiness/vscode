int delete_file(char *fname)
{
	DIR *d;
	struct dirent *di;
	char buf[MAXPATHLEN];
	extern int force_delete;
	STRUCT_STAT st;
	int ret;
	extern int recurse;

#if SUPPORT_LINKS
	ret = do_lstat(fname, &st);
#else
	ret = do_stat(fname, &st);
#endif
	if (ret) {
		return -1;
	}

	if (!S_ISDIR(st.st_mode)) {
		if (robust_unlink(fname) == 0 || errno == ENOENT) return 0;
		rprintf(FERROR, "delete_file: unlink %s failed: %s\n",
			full_fname(fname), strerror(errno));
		return -1;
	}

	if (do_rmdir(fname) == 0 || errno == ENOENT) return 0;
	if (!force_delete || !recurse ||
	    (errno != ENOTEMPTY && errno != EEXIST)) {
		rprintf(FERROR, "delete_file: rmdir %s failed: %s\n",
			full_fname(fname), strerror(errno));
		return -1;
	}

	/* now we do a recsursive delete on the directory ... */
	d = opendir(fname);
	if (!d) {
		rprintf(FERROR, "delete_file: opendir %s failed: %s\n",
			full_fname(fname), strerror(errno));
		return -1;
	}

	for (errno = 0, di = readdir(d); di; errno = 0, di = readdir(d)) {
		char *dname = d_name(di);
		if (strcmp(dname,".") == 0
		    || strcmp(dname,"..") == 0)
			continue;
		snprintf(buf, sizeof(buf), "%s/%s", fname, dname);
		if (verbose > 0)
			rprintf(FINFO,"deleting %s\n", buf);
		if (delete_file(buf) != 0) {
			closedir(d);
			return -1;
		}
	}
	if (errno) {
		rprintf(FERROR, "delete_file: readdir %s failed: %s\n",
			full_fname(fname), strerror(errno));
		closedir(d);
		return -1;
	}

	closedir(d);

	if (do_rmdir(fname) != 0) {
		rprintf(FERROR, "delete_file: rmdir %s failed: %s\n",
			full_fname(fname), strerror(errno));
		return -1;
	}

	return 0;
}