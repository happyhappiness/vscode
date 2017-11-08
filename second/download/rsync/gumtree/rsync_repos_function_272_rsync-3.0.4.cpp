static void delete_in_dir(char *fbuf, struct file_struct *file, dev_t *fs_dev)
{
	static int already_warned = 0;
	struct file_list *dirlist;
	char delbuf[MAXPATHLEN];
	int dlen, i;
	int save_uid_ndx = uid_ndx;

	if (!fbuf) {
		change_local_filter_dir(NULL, 0, 0);
		return;
	}

	if (verbose > 2)
		rprintf(FINFO, "delete_in_dir(%s)\n", fbuf);

	if (allowed_lull)
		maybe_send_keepalive();

	if (io_error && !ignore_errors) {
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

	if (!uid_ndx)
		uid_ndx = ++file_extra_cnt;

	dirlist = get_dirlist(fbuf, dlen, 0);

	/* If an item in dirlist is not found in flist, delete it
	 * from the filesystem. */
	for (i = dirlist->used; i--; ) {
		struct file_struct *fp = dirlist->files[i];
		if (!F_IS_ACTIVE(fp))
			continue;
		if (fp->flags & FLAG_MOUNT_DIR && S_ISDIR(fp->mode)) {
			if (verbose > 1)
				rprintf(FINFO, "cannot delete mount point: %s\n",
					f_name(fp, NULL));
			continue;
		}
		if (flist_find(cur_flist, fp) < 0) {
			int flags = DEL_RECURSE;
			if (!(fp->mode & S_IWUSR) && !am_root && (uid_t)F_OWNER(fp) == our_uid)
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

	if (!save_uid_ndx) {
		--file_extra_cnt;
		uid_ndx = 0;
	}
}