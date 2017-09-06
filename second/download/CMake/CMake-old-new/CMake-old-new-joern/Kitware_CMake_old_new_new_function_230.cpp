static int
next_entry(struct archive_read_disk *a, struct tree *t,
    struct archive_entry *entry)
{
	const BY_HANDLE_FILE_INFORMATION *st;
	const BY_HANDLE_FILE_INFORMATION *lst;
	const char*name;
	int descend, r;

	st = NULL;
	lst = NULL;
	t->descend = 0;
	do {
		switch (tree_next(t)) {
		case TREE_ERROR_FATAL:
			archive_set_error(&a->archive, t->tree_errno,
			    "%ls: Unable to continue traversing directory tree",
			    tree_current_path(t));
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		case TREE_ERROR_DIR:
			archive_set_error(&a->archive, t->tree_errno,
			    "%ls: Couldn't visit directory",
			    tree_current_path(t));
			return (ARCHIVE_FAILED);
		case 0:
			return (ARCHIVE_EOF);
		case TREE_POSTDESCENT:
		case TREE_POSTASCENT:
			break;
		case TREE_REGULAR:
			lst = tree_current_lstat(t);
			if (lst == NULL) {
				archive_set_error(&a->archive, t->tree_errno,
				    "%ls: Cannot stat",
				    tree_current_path(t));
				return (ARCHIVE_FAILED);
			}
			break;
		}	
	} while (lst == NULL);

	archive_entry_copy_pathname_w(entry, tree_current_path(t));

	/*
	 * Perform path matching.
	 */
	if (a->matching) {
		r = archive_match_path_excluded(a->matching, entry);
		if (r < 0) {
			archive_set_error(&(a->archive), errno,
			    "Failed : %s", archive_error_string(a->matching));
			return (r);
		}
		if (r) {
			if (a->excluded_cb_func)
				a->excluded_cb_func(&(a->archive),
				    a->excluded_cb_data, entry);
			return (ARCHIVE_RETRY);
		}
	}

	/*
	 * Distinguish 'L'/'P'/'H' symlink following.
	 */
	switch(t->symlink_mode) {
	case 'H':
		/* 'H': After the first item, rest like 'P'. */
		t->symlink_mode = 'P';
		/* 'H': First item (from command line) like 'L'. */
		/* FALLTHROUGH */
	case 'L':
		/* 'L': Do descend through a symlink to dir. */
		descend = tree_current_is_dir(t);
		/* 'L': Follow symlinks to files. */
		a->symlink_mode = 'L';
		a->follow_symlinks = 1;
		/* 'L': Archive symlinks as targets, if we can. */
		st = tree_current_stat(t);
		if (st != NULL && !tree_target_is_same_as_parent(t, st))
			break;
		/* If stat fails, we have a broken symlink;
		 * in that case, don't follow the link. */
		/* FALLTHROUGH */
	default:
		/* 'P': Don't descend through a symlink to dir. */
		descend = tree_current_is_physical_dir(t);
		/* 'P': Don't follow symlinks to files. */
		a->symlink_mode = 'P';
		a->follow_symlinks = 0;
		/* 'P': Archive symlinks as symlinks. */
		st = lst;
		break;
	}

	if (update_current_filesystem(a, bhfi_dev(st)) != ARCHIVE_OK) {
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}
	if (t->initial_filesystem_id == -1)
		t->initial_filesystem_id = t->current_filesystem_id;
	if (!a->traverse_mount_points) {
		if (t->initial_filesystem_id != t->current_filesystem_id)
			return (ARCHIVE_RETRY);
	}
	t->descend = descend;

	tree_archive_entry_copy_bhfi(entry, t, st);

	/* Save the times to be restored. This must be in before
	 * calling archive_read_disk_descend() or any chance of it,
	 * especially, invoking a callback. */
	t->restore_time.lastWriteTime = st->ftLastWriteTime;
	t->restore_time.lastAccessTime = st->ftLastAccessTime;
	t->restore_time.filetype = archive_entry_filetype(entry);

	/*
	 * Perform time matching.
	 */
	if (a->matching) {
		r = archive_match_time_excluded(a->matching, entry);
		if (r < 0) {
			archive_set_error(&(a->archive), errno,
			    "Failed : %s", archive_error_string(a->matching));
			return (r);
		}
		if (r) {
			if (a->excluded_cb_func)
				a->excluded_cb_func(&(a->archive),
				    a->excluded_cb_data, entry);
			return (ARCHIVE_RETRY);
		}
	}

	/* Lookup uname/gname */
	name = archive_read_disk_uname(&(a->archive), archive_entry_uid(entry));
	if (name != NULL)
		archive_entry_copy_uname(entry, name);
	name = archive_read_disk_gname(&(a->archive), archive_entry_gid(entry));
	if (name != NULL)
		archive_entry_copy_gname(entry, name);

	/*
	 * Perform owner matching.
	 */
	if (a->matching) {
		r = archive_match_owner_excluded(a->matching, entry);
		if (r < 0) {
			archive_set_error(&(a->archive), errno,
			    "Failed : %s", archive_error_string(a->matching));
			return (r);
		}
		if (r) {
			if (a->excluded_cb_func)
				a->excluded_cb_func(&(a->archive),
				    a->excluded_cb_data, entry);
			return (ARCHIVE_RETRY);
		}
	}

	/*
	 * Invoke a meta data filter callback.
	 */
	if (a->metadata_filter_func) {
		if (!a->metadata_filter_func(&(a->archive),
		    a->metadata_filter_data, entry))
			return (ARCHIVE_RETRY);
	}

	archive_entry_copy_sourcepath_w(entry, tree_current_access_path(t));

	r = ARCHIVE_OK;
	if (archive_entry_filetype(entry) == AE_IFREG &&
	    archive_entry_size(entry) > 0) {
		DWORD flags = FILE_FLAG_BACKUP_SEMANTICS;
		if (t->async_io)
			flags |= FILE_FLAG_OVERLAPPED;
		if (t->direct_io)
			flags |= FILE_FLAG_NO_BUFFERING;
		else
			flags |= FILE_FLAG_SEQUENTIAL_SCAN;
		t->entry_fh = CreateFileW(tree_current_access_path(t),
		    GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, flags, NULL);
		if (t->entry_fh == INVALID_HANDLE_VALUE) {
			archive_set_error(&a->archive, errno,
			    "Couldn't open %ls", tree_current_path(a->tree));
			return (ARCHIVE_FAILED);
		}

		/* Find sparse data from the disk. */
		if (archive_entry_hardlink(entry) == NULL &&
		    (st->dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE) != 0)
			r = setup_sparse_from_disk(a, entry, t->entry_fh);
	}
	return (r);
}