void generate_files(int f, struct file_list *flist, char *local_name)
{
	int i;
	int phase=0;
	char fbuf[MAXPATHLEN];

	if (verbose > 2) {
		rprintf(FINFO, "generator starting pid=%ld count=%d\n",
			(long)getpid(), flist->count);
	}

	if (verbose >= 2) {
		rprintf(FINFO,
			disable_deltas_p()
			? "delta-transmission disabled for local transfer or --whole-file\n"
			: "delta transmission enabled\n");
	}

	/* we expect to just sit around now, so don't exit on a
	   timeout. If we really get a timeout then the other process should
	   exit */
	io_timeout = 0;

	for (i = 0; i < flist->count; i++) {
		struct file_struct *file = flist->files[i];
		struct file_struct copy;

		if (!file->basename)
			continue;
		/* we need to ensure that any directories we create have writeable
		   permissions initially so that we can create the files within
		   them. This is then fixed after the files are transferred */
		if (!am_root && S_ISDIR(file->mode) && !(file->mode & S_IWUSR)) {
			copy = *file;
			/* XXX: Could this be causing a problem on SCO?  Perhaps their
			 * handling of permissions is strange? */
			copy.mode |= S_IWUSR; /* user write */
			file = &copy;
		}

		recv_generator(local_name ? local_name : f_name_to(file, fbuf),
			       file, i, f);
	}

	phase++;
	csum_length = SUM_LENGTH;
	ignore_times=1;

	if (verbose > 2)
		rprintf(FINFO,"generate_files phase=%d\n",phase);

	write_int(f,-1);

	/* files can cycle through the system more than once
	 * to catch initial checksum errors */
	while ((i = get_redo_num()) != -1) {
		struct file_struct *file = flist->files[i];
		recv_generator(local_name ? local_name : f_name_to(file, fbuf),
			       file, i, f);
	}

	phase++;
	if (verbose > 2)
		rprintf(FINFO,"generate_files phase=%d\n",phase);

	write_int(f,-1);

	if (preserve_hard_links)
		do_hard_links();

	/* now we need to fix any directory permissions that were
	 * modified during the transfer */
	for (i = 0; i < flist->count; i++) {
		struct file_struct *file = flist->files[i];
		if (!file->basename || !S_ISDIR(file->mode)) continue;
		recv_generator(local_name ? local_name : f_name(file),
			       file, i, -1);
	}

	if (verbose > 2)
		rprintf(FINFO,"generate_files finished\n");
}