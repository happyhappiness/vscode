	int l;
	char *p;

	d = opendir(dir);
	if (!d) {
		io_error = 1;
		rprintf(FERROR,"%s: %s\n",
			dir,strerror(errno));
		return;
	}

	strlcpy(fname,dir,MAXPATHLEN-1);
	l = strlen(fname);
	if (fname[l-1] != '/') {
		if (l == MAXPATHLEN-1) {
			io_error = 1;
			rprintf(FERROR,"skipping long-named directory %s\n",fname);
			closedir(d);
			return;
		}
		strcat(fname,"/");
		l++;
	}
