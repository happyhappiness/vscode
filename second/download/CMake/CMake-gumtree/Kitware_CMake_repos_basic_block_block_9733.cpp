{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_read_next_header2");

	t = a->tree;
	if (t->entry_fd >= 0) {
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
	}

	for (;;) {
		r = next_entry(a, t, entry);
		if (t->entry_fd >= 0) {
			close(t->entry_fd);
			t->entry_fd = -1;
		}

		if (r == ARCHIVE_RETRY) {
			archive_entry_clear(entry);
			continue;
		}
		break;
	}

	/* Return to the initial directory. */
	tree_enter_initial_dir(t);

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
		/* Overwrite the sourcepath based on the initial directory. */
		archive_entry_copy_sourcepath(entry, tree_current_path(t));
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

	__archive_reset_read_data(&a->archive);
	return (r);
}