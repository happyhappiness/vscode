struct file_list *get_dirlist(char *dirname, int dlen, int ignore_filter_rules)
{
	struct file_list *dirlist;
	char dirbuf[MAXPATHLEN];
	int save_recurse = recurse;
	int save_xfer_dirs = xfer_dirs;
	int save_prune_empty_dirs = prune_empty_dirs;

	if (dlen < 0) {
		dlen = strlcpy(dirbuf, dirname, MAXPATHLEN);
		if (dlen >= MAXPATHLEN)
			return NULL;
		dirname = dirbuf;
	}

	dirlist = flist_new(FLIST_TEMP, "get_dirlist");

	recurse = 0;
	xfer_dirs = 1;
	send_directory(ignore_filter_rules ? -2 : -1, dirlist, dirname, dlen, 0);
	xfer_dirs = save_xfer_dirs;
	recurse = save_recurse;
	if (do_progress)
		flist_count_offset += dirlist->used;

	prune_empty_dirs = 0;
	dirlist->sorted = dirlist->files;
	flist_sort_and_clean(dirlist, 0);
	prune_empty_dirs = save_prune_empty_dirs;

	if (verbose > 3)
		output_flist(dirlist);

	return dirlist;
}