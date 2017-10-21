	return (st2.st_dev != filesystem_dev);
}

static struct file_struct *make_file(char *fname)
{
	struct file_struct *file;
	struct stat st;
	char sum[SUM_LENGTH];
	char *p;
	char cleaned_name[MAXPATHLEN];

	strncpy(cleaned_name, fname, MAXPATHLEN-1);
	cleaned_name[MAXPATHLEN-1] = 0;
	clean_fname(cleaned_name);
	fname = cleaned_name;

	bzero(sum,SUM_LENGTH);

	if (link_stat(fname,&st) != 0) {
		io_error = 1;
		fprintf(FERROR,"%s: %s\n",
			fname,strerror(errno));
		return NULL;
	}

	if (S_ISDIR(st.st_mode) && !recurse) {
		fprintf(FINFO,"skipping directory %s\n",fname);
		return NULL;
	}
	
	if (one_file_system && st.st_dev != filesystem_dev) {
		if (skip_filesystem(fname, &st))
			return NULL;
	}
	
	if (!match_file_name(fname,&st))
		return NULL;
	
	if (verbose > 2)
		fprintf(FINFO,"make_file(%s)\n",fname);
	
	file = (struct file_struct *)malloc(sizeof(*file));
	if (!file) out_of_memory("make_file");
	bzero((char *)file,sizeof(*file));

	if ((p = strrchr(fname,'/'))) {
