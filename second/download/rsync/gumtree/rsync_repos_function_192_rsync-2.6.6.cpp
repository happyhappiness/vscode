static void do_delete_pass(struct file_list *flist)
{
	char fbuf[MAXPATHLEN];
	int j;

	if (dry_run > 1 /* destination doesn't exist yet */
	 || list_only)
		return;

	for (j = 0; j < flist->count; j++) {
		struct file_struct *file = flist->files[j];

		if (!(file->flags & FLAG_DEL_HERE))
			continue;

		f_name_to(file, fbuf);
		if (verbose > 1 && file->flags & FLAG_TOP_DIR)
			rprintf(FINFO, "deleting in %s\n", safe_fname(fbuf));

		delete_in_dir(flist, fbuf, file);
	}
	if (do_progress && !am_server)
		rprintf(FINFO, "                    \r");
}