static int delete_file(char *fname)
{
	DIR *d;
	struct dirent *di;
	char buf[MAXPATHLEN];
	extern int force_delete;
	STRUCT_STAT st;
	int ret;

	if (do_unlink(fname) == 0 || errno == ENOENT) return 0;

#if SUPPORT_LINKS
	ret = do_lstat(fname, &st);
#else
	ret = do_stat(fname, &st);
#endif
	if (ret) {
		rprintf(FERROR,"stat(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	if (!S_ISDIR(st.st_mode)) {
		rprintf(FERROR,"unlink(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	if (do_rmdir(fname) == 0 || errno == ENOENT) return 0;
	if (!force_delete || (errno != ENOTEMPTY && errno != EEXIST)) {
		rprintf(FERROR,"rmdir(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	/* now we do a recsursive delete on the directory ... */
	d = opendir(fname);
	if (!d) {
		rprintf(FERROR,"opendir(%s): %s\n",
			fname,strerror(errno));
		return -1;
	}

	for (di=readdir(d); di; di=readdir(d)) {
		char *dname = d_name(di);
		if (strcmp(dname,".")==0 ||
		    strcmp(dname,"..")==0)
			continue;
		strlcpy(buf, fname, (MAXPATHLEN-strlen(dname))-2);
		strcat(buf, "/");
		strcat(buf, dname);
		buf[MAXPATHLEN-1] = 0;
		if (verbose > 0)
			rprintf(FINFO,"deleting %s\n", buf);
		if (delete_file(buf) != 0) {
			closedir(d);
			return -1;
		}
	}	

	closedir(d);
	
	if (do_rmdir(fname) != 0) {
		rprintf(FERROR,"rmdir(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	return 0;
}

