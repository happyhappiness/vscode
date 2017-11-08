void successful_send(int ndx)
{
	char fname[MAXPATHLEN];
	struct file_struct *file;
	unsigned int offset;

	if (ndx < 0 || ndx >= the_file_list->count)
		return;

	file = the_file_list->files[ndx];
	/* The generator might tell us about symlinks we didn't send. */
	if (!(file->flags & FLAG_SENT) && !S_ISLNK(file->mode))
		return;
	if (file->dir.root) {
		offset = stringjoin(fname, sizeof fname,
				    file->dir.root, "/", NULL);
	} else
		offset = 0;
	f_name(file, fname + offset);
	if (remove_sent_files && do_unlink(fname) == 0 && verbose > 1)
		rprintf(FINFO, "sender removed %s\n", fname + offset);
}