static void delete_in_dir(char *fbuf, struct file_struct *file, dev_t *fs_dev)
{
	static int already_warned = 0;
	struct file_list *dirlist;
	char delbuf[MAXPATHLEN];
	int dlen, i;

	if (!fbuf) {
		change_local_filter_dir(NULL, 0, 0);
		return;
	}

	if (DEBUG_GTE(DEL, 2))
		rprintf(FINFO, "delete_in_dir(%s)\n", fbuf);

	if (allowed_lull)
		maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);

	if (io_error & IOERR_GENERAL && !ignore_errors) {
		if (already_warned)
			return;
		rprintf(FINFO,
			"IO error encountered -- skipping file deletion\n");
		already_warned = 1;
		return;
	}

	dlen = strlen(fbuf);
	change_local_filter_dir(fbuf, dlen, F_DEPTH(file));

	if (one_file_system) {
		if (file->flags & FLAG_TOP_DIR)
			filesystem_dev = *fs_dev;
		else if (filesystem_dev != *fs_dev)
			return;
	}

	dirlist = get_dirlist(fbuf, dlen, 0);

	/* If an item in dirlist is not found in flist, delete it
	 * from the filesystem. */
	for (i = dirlist->used; i--; ) {
		struct file_struct *fp = dirlist->files[i];
		if (!F_IS_ACTIVE(fp))
			continue;
		if (fp->flags & FLAG_MOUNT_DIR && S_ISDIR(fp->mode)) {
			if (INFO_GTE(MOUNT, 1))
				rprintf(FINFO, "cannot delete mount point: %s\n",
					f_name(fp, NULL));
			continue;
		}
		/* Here we want to match regardless of file type.  Replacement
		 * of a file with one of another type is handled separately by
		 * a delete_item call with a DEL_MAKE_ROOM flag. */
		if (flist_find_ignore_dirness(cur_flist, fp) < 0) {
			int flags = DEL_RECURSE;
			if (!(fp->mode & S_IWUSR) && !am_root && fp->flags & FLAG_OWNED_BY_US)
				flags |= DEL_NO_UID_WRITE;
			f_name(fp, delbuf);
			if (delete_during == 2) {
				if (!remember_delete(fp, delbuf, flags))
					break;
			} else
				delete_item(delbuf, fp->mode, flags);
		}
	}

	flist_free(dirlist);
}