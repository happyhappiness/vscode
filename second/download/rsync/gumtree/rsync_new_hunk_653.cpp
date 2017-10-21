
      skip_excludes:

	if (verbose > 2)
		rprintf(FINFO, "make_file(%d,%s)\n", f, fname);

	file = new(struct file_struct);
	if (!file)
		out_of_memory("make_file");
	memset((char *) file, 0, sizeof(*file));

	if ((p = strrchr(fname, '/'))) {
		static char *lastdir;
