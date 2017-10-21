	if (!S_ISDIR(st.st_mode)) {
		fprintf(FERROR,"unlink(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	if (do_rmdir(fname) == 0 || errno == ENOENT) return 0;
	if (!force_delete || (errno != ENOTEMPTY && errno != EEXIST)) {
		fprintf(FERROR,"rmdir(%s) : %s\n", fname, strerror(errno));
		return -1;
	}

	/* now we do a recsursive delete on the directory ... */
	d = opendir(fname);
