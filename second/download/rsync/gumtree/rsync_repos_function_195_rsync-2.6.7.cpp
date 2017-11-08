static void delete_in_dir(struct file_list *flist, char *fbuf,
			  struct file_struct *file, STRUCT_STAT *stp)
{
	static int min_depth = MAXPATHLEN, cur_depth = -1;
	static void *filt_array[MAXPATHLEN/2+1];
	static int already_warned = 0;
	struct file_list *dirlist;
	char delbuf[MAXPATHLEN];
	int dlen, i;

	if (!flist) {
		while (cur_depth >= min_depth)
			pop_local_filters(filt_array[cur_depth--]);
		min_depth = MAXPATHLEN;
		cur_depth = -1;
		return;
	}

	if (verbose > 2)
		rprintf(FINFO, "delete_in_dir(%s)\n", fbuf);

	if (allowed_lull)
		maybe_send_keepalive();

	if (file->dir.depth >= MAXPATHLEN/2+1)
		return; /* Impossible... */

	if (io_error && !(lp_ignore_errors(module_id) || ignore_errors)) {
		if (already_warned)
			return;
		rprintf(FINFO,
			"IO error encountered -- skipping file deletion\n");
		already_warned = 1;
		return;
	}

	while (cur_depth >= file->dir.depth && cur_depth >= min_depth)
		pop_local_filters(filt_array[cur_depth--]);
	cur_depth = file->dir.depth;
	if (min_depth > cur_depth)
		min_depth = cur_depth;
	dlen = strlen(fbuf);
	filt_array[cur_depth] = push_local_filters(fbuf, dlen);

	if (one_file_system) {
		if (file->flags & FLAG_TOP_DIR)
			filesystem_dev = stp->st_dev;
		else if (filesystem_dev != stp->st_dev)
			return;
	}

	dirlist = get_dirlist(fbuf, dlen, 0);

	/* If an item in dirlist is not found in flist, delete it
	 * from the filesystem. */
	for (i = dirlist->count; i--; ) {
		struct file_struct *fp = dirlist->files[i];
		if (!fp->basename || fp->flags & FLAG_MOUNT_POINT)
			continue;
		if (flist_find(flist, fp) < 0) {
			f_name(fp, delbuf);
			delete_item(delbuf, fp->mode, DEL_FORCE_RECURSE);
		}
	}

	flist_free(dirlist);
}