static void do_delete_pass(void)
{
	char fbuf[MAXPATHLEN];
	STRUCT_STAT st;
	int j;

	/* dry_run is incremented when the destination doesn't exist yet. */
	if (dry_run > 1 || list_only)
		return;

	for (j = 0; j < cur_flist->used; j++) {
		struct file_struct *file = cur_flist->sorted[j];

		if (!F_IS_ACTIVE(file))
			continue;

		f_name(file, fbuf);

		if (!(file->flags & FLAG_CONTENT_DIR)) {
			change_local_filter_dir(fbuf, strlen(fbuf), F_DEPTH(file));
			continue;
		}

		if (DEBUG_GTE(DEL, 1) && file->flags & FLAG_TOP_DIR)
			rprintf(FINFO, "deleting in %s\n", fbuf);

		if (link_stat(fbuf, &st, keep_dirlinks) < 0
		 || !S_ISDIR(st.st_mode))
			continue;

		delete_in_dir(fbuf, file, &st.st_dev);
	}
	delete_in_dir(NULL, NULL, &dev_zero);

	if (INFO_GTE(FLIST, 2) && !am_server)
		rprintf(FINFO, "                    \r");
}