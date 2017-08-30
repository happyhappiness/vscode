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
