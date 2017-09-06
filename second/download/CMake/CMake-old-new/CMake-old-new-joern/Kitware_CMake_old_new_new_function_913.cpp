static int
_archive_read_data_block(struct archive *_a, const void **buff,
    size_t *size, int64_t *offset)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t = a->tree;
	struct la_overlapped *olp;
	DWORD bytes_transferred;
	int r = ARCHIVE_FATAL;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,
	    "archive_read_data_block");

	if (t->entry_eof || t->entry_remaining_bytes <= 0) {
		r = ARCHIVE_EOF;
		goto abort_read_data;
	}

	/*
	 * Make a request to read the file in asynchronous.
	 */
	if (t->ol_num_doing == 0) {
		do {
			r = start_next_async_read(a, t);
			if (r == ARCHIVE_FATAL)
				goto abort_read_data;
			if (!t->async_io)
				break;
		} while (r == ARCHIVE_OK && t->ol_num_doing < MAX_OVERLAPPED);
	} else {
		if (start_next_async_read(a, t) == ARCHIVE_FATAL)
			goto abort_read_data;
	}

	olp = &(t->ol[t->ol_idx_done]);
	t->ol_idx_done = (t->ol_idx_done + 1) % MAX_OVERLAPPED;
	if (olp->bytes_transferred)
		bytes_transferred = (DWORD)olp->bytes_transferred;
	else if (!GetOverlappedResult(t->entry_fh, &(olp->ol),
	    &bytes_transferred, TRUE)) {
		la_dosmaperr(GetLastError());
		archive_set_error(&a->archive, errno,
		    "GetOverlappedResult failed");
		a->archive.state = ARCHIVE_STATE_FATAL;
		r = ARCHIVE_FATAL;
		goto abort_read_data;
	}
	t->ol_num_done++;

	if (bytes_transferred == 0 ||
	    olp->bytes_expected != bytes_transferred) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Reading file truncated");
		a->archive.state = ARCHIVE_STATE_FATAL;
		r = ARCHIVE_FATAL;
		goto abort_read_data;
	}

	*buff = olp->buff;
	*size = bytes_transferred;
	*offset = olp->offset;
	if (olp->offset > t->entry_total)
		t->entry_remaining_bytes -= olp->offset - t->entry_total;
	t->entry_total = olp->offset + *size;
	t->entry_remaining_bytes -= *size;
	if (t->entry_remaining_bytes == 0) {
		/* Close the current file descriptor */
		close_and_restore_time(t->entry_fh, t, &t->restore_time);
		t->entry_fh = INVALID_HANDLE_VALUE;
		t->entry_eof = 1;
	}
	return (ARCHIVE_OK);

abort_read_data:
	*buff = NULL;
	*size = 0;
	*offset = t->entry_total;
	if (t->entry_fh != INVALID_HANDLE_VALUE) {
		cancel_async(t);
		/* Close the current file descriptor */
		close_and_restore_time(t->entry_fh, t, &t->restore_time);
		t->entry_fh = INVALID_HANDLE_VALUE;
	}
	return (r);
}