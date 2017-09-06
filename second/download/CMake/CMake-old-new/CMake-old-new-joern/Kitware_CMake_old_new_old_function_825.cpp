static int
_archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t;
	const BY_HANDLE_FILE_INFORMATION *st;
	const BY_HANDLE_FILE_INFORMATION *lst;
	const char*name;
	int descend, r;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_read_next_header2");

	t = a->tree;
	if (t->entry_fh != INVALID_HANDLE_VALUE) {
		close_and_restore_time(t->entry_fh, t, &t->restore_time);
		t->entry_fh = INVALID_HANDLE_VALUE;
	}
	st = NULL;
	lst = NULL;
	do {
		switch (tree_next(t)) {
		case TREE_ERROR_FATAL:
			archive_set_error(&a->archive, t->tree_errno,
			    "%ls: Unable to continue traversing directory tree",
			    tree_current_path(t));
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		case TREE_ERROR_DIR:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
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
				archive_set_error(&a->archive, errno,
				    "%ls: Cannot stat",
				    tree_current_path(t));
				return (ARCHIVE_FAILED);
			}
			break;
		}	
	} while (lst == NULL);

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
	t->descend = descend;

	archive_entry_copy_pathname_w(entry, tree_current_path(t));
	archive_entry_copy_sourcepath_w(entry, tree_current_access_path(t));
	tree_archive_entry_copy_bhfi(entry, t, st);

	/* Save the times to be restored. */
	t->restore_time.lastWriteTime = st->ftLastWriteTime;
	t->restore_time.lastAccessTime = st->ftLastAccessTime;
	t->restore_time.filetype = archive_entry_filetype(entry);

	/* Lookup uname/gname */
	name = archive_read_disk_uname(_a, archive_entry_uid(entry));
	if (name != NULL)
		archive_entry_copy_uname(entry, name);
	name = archive_read_disk_gname(_a, archive_entry_gid(entry));
	if (name != NULL)
		archive_entry_copy_gname(entry, name);

	r = ARCHIVE_OK;
	if (archive_entry_filetype(entry) == AE_IFREG &&
	    archive_entry_size(entry) > 0) {
		t->entry_fh = CreateFileW(tree_current_access_path(t),
		    GENERIC_READ, 0, NULL, OPEN_EXISTING,
		    FILE_FLAG_SEQUENTIAL_SCAN, NULL);
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

	/*
	 * EOF and FATAL are persistent at this layer.  By
	 * modifying the state, we guarantee that future calls to
	 * read a header or read data will fail.
	 */
	switch (r) {
	case ARCHIVE_EOF:
		a->archive.state = ARCHIVE_STATE_EOF;
		break;
	case ARCHIVE_OK:
	case ARCHIVE_WARN:
		t->entry_total = 0;
		if (archive_entry_filetype(entry) == AE_IFREG) {
			t->entry_remaining_bytes = archive_entry_size(entry);
			t->entry_eof = (t->entry_remaining_bytes == 0)? 1: 0;
			if (!t->entry_eof &&
			    setup_sparse(a, entry) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
		} else {
			t->entry_remaining_bytes = 0;
			t->entry_eof = 1;
		}
		a->archive.state = ARCHIVE_STATE_DATA;
		break;
	case ARCHIVE_RETRY:
		break;
	case ARCHIVE_FATAL:
		a->archive.state = ARCHIVE_STATE_FATAL;
		break;
	}

	return (r);
}