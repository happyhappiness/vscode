	return (NULL);
}

static int64_t
align_num_per_sector(struct tree *t, int64_t size)
{
	int64_t surplus;

	size += t->current_filesystem->bytesPerSector -1;
	surplus = size % t->current_filesystem->bytesPerSector;
	size -= surplus;
	return (size);
}

static int
start_next_async_read(struct archive_read_disk *a, struct tree *t)
{
	struct la_overlapped *olp;
	DWORD buffbytes, rbytes;

	if (t->ol_remaining_bytes == 0)
		return (ARCHIVE_EOF);

	olp = &(t->ol[t->ol_idx_doing]);
	t->ol_idx_doing = (t->ol_idx_doing + 1) % MAX_OVERLAPPED;

	/* Allocate read buffer. */
	if (olp->buff == NULL) {
		void *p;
		size_t s = (size_t)align_num_per_sector(t, BUFFER_SIZE);
		p = VirtualAlloc(NULL, s, MEM_COMMIT, PAGE_READWRITE);
		if (p == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Couldn't allocate memory");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}
		olp->buff = p;
		olp->buff_size = s;
		olp->_a = &a->archive;
		olp->ol.hEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
		if (olp->ol.hEvent == NULL) {
			la_dosmaperr(GetLastError());
			archive_set_error(&a->archive, errno,
			    "CreateEvent failed");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}
	} else
		ResetEvent(olp->ol.hEvent);

	buffbytes = (DWORD)olp->buff_size;
	if (buffbytes > t->current_sparse->length)
		buffbytes = (DWORD)t->current_sparse->length;

	/* Skip hole. */
	if (t->current_sparse->offset > t->ol_total) {
		t->ol_remaining_bytes -=
			t->current_sparse->offset - t->ol_total;
	}

	olp->offset = t->current_sparse->offset;
	olp->ol.Offset = (DWORD)(olp->offset & 0xffffffff);
	olp->ol.OffsetHigh = (DWORD)(olp->offset >> 32);

	if (t->ol_remaining_bytes > buffbytes) {
		olp->bytes_expected = buffbytes;
		t->ol_remaining_bytes -= buffbytes;
	} else {
		olp->bytes_expected = (size_t)t->ol_remaining_bytes;
		t->ol_remaining_bytes = 0;
	}
	olp->bytes_transferred = 0;
	t->current_sparse->offset += buffbytes;
	t->current_sparse->length -= buffbytes;
	t->ol_total = t->current_sparse->offset;
	if (t->current_sparse->length == 0 && t->ol_remaining_bytes > 0)
		t->current_sparse++;

	if (!ReadFile(t->entry_fh, olp->buff, buffbytes, &rbytes, &(olp->ol))) {
		DWORD lasterr;

		lasterr = GetLastError();
		if (lasterr == ERROR_HANDLE_EOF) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Reading file truncated");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		} else if (lasterr != ERROR_IO_PENDING) {
			if (lasterr == ERROR_NO_DATA)
				errno = EAGAIN;
			else if (lasterr == ERROR_ACCESS_DENIED)
				errno = EBADF;
			else
				la_dosmaperr(lasterr);
			archive_set_error(&a->archive, errno, "Read error");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}
	} else
		olp->bytes_transferred = rbytes;
	t->ol_num_doing++;

	return (t->ol_remaining_bytes == 0)? ARCHIVE_EOF: ARCHIVE_OK;
}

static void
cancel_async(struct tree *t)
{
	if (t->ol_num_doing != t->ol_num_done) {
		CancelIo(t->entry_fh);
		t->ol_num_doing = t->ol_num_done = 0;
	}
}

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
