	
	if (verbose > 2)
		rprintf(FINFO,"make_file(%s)\n",fname);
	
	file = (struct file_struct *)malloc(sizeof(*file));
	if (!file) out_of_memory("make_file");
	memset((char *)file,0,sizeof(*file));

	if ((p = strrchr(fname,'/'))) {
		static char *lastdir;
		*p = 0;
		if (lastdir && strcmp(fname, lastdir)==0) {
			file->dirname = lastdir;
