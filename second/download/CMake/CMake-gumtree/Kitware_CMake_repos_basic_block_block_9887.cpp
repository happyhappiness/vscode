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