static void do_delete_pass(struct file_list *flist)
{
	char fbuf[MAXPATHLEN];
	STRUCT_STAT st;
	int j;

	/* dry_run is incremented when the destination doesn't exist yet. */
	if (dry_run > 1 || list_only)
		return;

	for (j = 0; j < flist->count; j++) {
		struct file_struct *file = flist->files[j];

		if (!(file->flags & FLAG_DEL_HERE))
			continue;

		f_name(file, fbuf);
		if (verbose > 1 && file->flags & FLAG_TOP_DIR)
			rprintf(FINFO, "deleting in %s\n", fbuf);

		if (link_stat(fbuf, &st, keep_dirlinks) < 0
		 || !S_ISDIR(st.st_mode))
			continue;

		delete_in_dir(flist, fbuf, file, &st);
	}
	delete_in_dir(NULL, NULL, NULL, NULL);

	if (do_progress && !am_server)
		rprintf(FINFO, "                    \r");
}