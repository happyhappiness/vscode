void successful_send(int ndx)
{
	char fname[MAXPATHLEN];
	struct file_struct *file;
	struct file_list *flist;

	if (!remove_source_files)
		return;

	flist = flist_for_ndx(ndx, "successful_send");
	file = flist->files[ndx - flist->ndx_start];
	if (!change_pathname(file, NULL, 0))
		return;
	f_name(file, fname);

	if (do_unlink(fname) == 0) {
		if (verbose > 1)
			rprintf(FINFO, "sender removed %s\n", fname);
	} else
		rsyserr(FERROR, errno, "sender failed to remove %s", fname);
}