	
	if (one_file_system && st.st_dev != filesystem_dev) {
		if (skip_filesystem(fname, &st))
			return NULL;
	}
	
	if (!match_file_name(fname,&st))
		return NULL;
	
	if (verbose > 2)
		rprintf(FINFO,"make_file(%s)\n",fname);
	
	file = (struct file_struct *)malloc(sizeof(*file));
	if (!file) out_of_memory("make_file");
	memset((char *)file,0,sizeof(*file));

	if ((p = strrchr(fname,'/'))) {
