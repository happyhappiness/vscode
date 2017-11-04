static int delete_file(char *fname)
{
	DIR *d;
	struct dirent *di;
	char buf[MAXPATHLEN];
	extern int force_delete;
	struct stat st;
	int ret;

	if (do_unlink(fname) == 0 || errno == ENOENT) return 0;

#if SUPPORT_LINKS
	ret = lstat(fname, &st);
#else
	ret = stat(fname, &st);
#endif
	if (ret) {
		fprintf(FERROR,"stat(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	if (!S_ISDIR(st.st_mode)) {
		fprintf(FERROR,"unlink(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	if (do_rmdir(fname) == 0 || errno == ENOENT) return 0;
	if (!force_delete || errno != ENOTEMPTY) {
		fprintf(FERROR,"rmdir(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	/* now we do a recsursive delete on the directory ... */
	d = opendir(fname);
	if (!d) {
		fprintf(FERROR,"opendir(%s): %s\n",
			fname,strerror(errno));
		return -1;
	}

	for (di=readdir(d); di; di=readdir(d)) {
		if (strcmp(di->d_name,".")==0 ||
		    strcmp(di->d_name,"..")==0)
			continue;
		strncpy(buf, fname, (MAXPATHLEN-strlen(di->d_name))-2);
		strcat(buf, "/");
		strcat(buf, di->d_name);
		buf[MAXPATHLEN-1] = 0;
		if (verbose > 0)
			fprintf(FINFO,"deleting %s\n", buf);
		if (delete_file(buf) != 0) {
			closedir(d);
			return -1;
		}
	}	

	closedir(d);
	
	if (do_rmdir(fname) != 0) {
		fprintf(FERROR,"rmdir(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	return 0;
}