struct file_list *get_dirlist(char *dirname, int dlen,
			      int ignore_filter_rules)
{
	struct file_list *dirlist;
	char dirbuf[MAXPATHLEN];
	int save_recurse = recurse;

	if (dlen < 0) {
		dlen = strlcpy(dirbuf, dirname, MAXPATHLEN);
		if (dlen >= MAXPATHLEN)
			return NULL;
		dirname = dirbuf;
	}

	dirlist = flist_new(WITHOUT_HLINK, "get_dirlist");

	recurse = 0;
	send_directory(ignore_filter_rules ? -2 : -1, dirlist, dirname, dlen);
	recurse = save_recurse;
	if (do_progress)
		flist_count_offset += dirlist->count;

	clean_flist(dirlist, 0, 0);

	if (verbose > 3)
		output_flist(dirlist);

	return dirlist;
}