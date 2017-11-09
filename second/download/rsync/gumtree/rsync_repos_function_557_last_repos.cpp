struct file_list *get_dirlist(char *dirname, int dlen, int flags)
{
	struct file_list *dirlist;
	char dirbuf[MAXPATHLEN];
	int save_recurse = recurse;
	int save_xfer_dirs = xfer_dirs;
	int save_prune_empty_dirs = prune_empty_dirs;
	int senddir_fd = flags & GDL_IGNORE_FILTER_RULES ? -2 : -1;

	if (dlen < 0) {
		dlen = strlcpy(dirbuf, dirname, MAXPATHLEN);
		if (dlen >= MAXPATHLEN)
			return NULL;
		dirname = dirbuf;
	}

	dirlist = flist_new(FLIST_TEMP, "get_dirlist");

	recurse = 0;
	xfer_dirs = 1;
	send_directory(senddir_fd, dirlist, dirname, dlen, FLAG_CONTENT_DIR);
	xfer_dirs = save_xfer_dirs;
	recurse = save_recurse;
	if (INFO_GTE(PROGRESS, 1))
		flist_count_offset += dirlist->used;

	prune_empty_dirs = 0;
	dirlist->sorted = dirlist->files;
	flist_sort_and_clean(dirlist, 0);
	prune_empty_dirs = save_prune_empty_dirs;

	if (DEBUG_GTE(FLIST, 3))
		output_flist(dirlist);

	return dirlist;
}