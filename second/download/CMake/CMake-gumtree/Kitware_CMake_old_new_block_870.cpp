{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t;
	const struct stat *st; /* info to use for this entry */
	const struct stat *lst;/* lstat() information */
	int descend, fd = -1, r;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_read_next_header2");

	t = a->tree;
	if (t->entry_fd >= 0) {
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
	}
#if !(defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR))
	/* Restore working directory. */
	tree_enter_working_dir(t);
#endif
	st = NULL;
	lst = NULL;
	do {
		switch (tree_next(t)) {
		case TREE_ERROR_FATAL:
			archive_set_error(&a->archive, t->tree_errno,
			    "%s: Unable to continue traversing directory tree",
			    tree_current_path(t));
			a->archive.state = ARCHIVE_STATE_FATAL;
			tree_enter_initial_dir(t);
			return (ARCHIVE_FATAL);
		case TREE_ERROR_DIR:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "%s: Couldn't visit directory",
			    tree_current_path(t));
			tree_enter_initial_dir(t);
			return (ARCHIVE_FAILED);
		case 0:
			tree_enter_initial_dir(t);
			return (ARCHIVE_EOF);
		case TREE_POSTDESCENT:
		case TREE_POSTASCENT:
			break;
		case TREE_REGULAR:
			lst = tree_current_lstat(t);
			if (lst == NULL) {
				archive_set_error(&a->archive, errno,
				    "%s: Cannot stat",
				    tree_current_path(t));
				tree_enter_initial_dir(t);
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

	if (update_current_filesystem(a, st->st_dev) != ARCHIVE_OK) {
		a->archive.state = ARCHIVE_STATE_FATAL;
		tree_enter_initial_dir(t);
		return (ARCHIVE_FATAL);
	}
	t->descend = descend;

	archive_entry_set_pathname(entry, tree_current_path(t));
	archive_entry_copy_sourcepath(entry, tree_current_access_path(t));
	archive_entry_copy_stat(entry, st);

	/* Save the times to be restored. */
	t->restore_time.mtime = archive_entry_mtime(entry);
	t->restore_time.mtime_nsec = archive_entry_mtime_nsec(entry);
	t->restore_time.atime = archive_entry_atime(entry);
	t->restore_time.atime_nsec = archive_entry_atime_nsec(entry);
	t->restore_time.filetype = archive_entry_filetype(entry);
	t->restore_time.noatime = t->current_filesystem->noatime;

#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
	/*
	 * Open the current file to freely gather its metadata anywhere in
	 * working directory.
	 * Note: A symbolic link file cannot be opened with O_NOFOLLOW.
	 */
	if (a->follow_symlinks || archive_entry_filetype(entry) != AE_IFLNK)
		fd = openat(tree_current_dir_fd(t), tree_current_access_path(t),
		    O_RDONLY | O_NONBLOCK);
	/* Restore working directory if openat() operation failed or
	 * the file is a symbolic link. */
	if (fd < 0)
		tree_enter_working_dir(t);

	/* The current direcotry fd is needed at
	 * archive_read_disk_entry_from_file() function to read link data
	 * with readlinkat(). */
	a->entry_wd_fd = tree_current_dir_fd(t);
#endif

	/*
	 * Populate the archive_entry with metadata from the disk.
	 */
	r = archive_read_disk_entry_from_file(&(a->archive), entry, fd, st);

	/* Close the file descriptor used for reding the current file
	 * metadata at archive_read_disk_entry_from_file(). */
	if (fd >= 0)
		close(fd);

	/* Return to the initial directory. */
	tree_enter_initial_dir(t);
	archive_entry_copy_sourcepath(entry, tree_current_path(t));

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
			t->nlink = archive_entry_nlink(entry);
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