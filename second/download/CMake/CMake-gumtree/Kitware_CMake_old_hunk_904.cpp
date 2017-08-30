	return (NULL);

}



static int

_archive_read_data_block(struct archive *_a, const void **buff,

    size_t *size, int64_t *offset)

{

	struct archive_read_disk *a = (struct archive_read_disk *)_a;

	struct tree *t = a->tree;

	int r;

	int64_t bytes;

	size_t buffbytes;



	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,

	    "archive_read_data_block");



	if (t->entry_eof || t->entry_remaining_bytes <= 0) {

		r = ARCHIVE_EOF;

		goto abort_read_data;

	}



	/* Allocate read buffer. */

	if (t->entry_buff == NULL) {

		t->entry_buff = malloc(1024 * 64);

		if (t->entry_buff == NULL) {

			archive_set_error(&a->archive, ENOMEM,

			    "Couldn't allocate memory");

			r = ARCHIVE_FATAL;

			a->archive.state = ARCHIVE_STATE_FATAL;

			goto abort_read_data;

		}

		t->entry_buff_size = 1024 * 64;

	}



	buffbytes = t->entry_buff_size;

	if (buffbytes > t->current_sparse->length)

		buffbytes = t->current_sparse->length;



	/*

	 * Skip hole.

	 */

	if (t->current_sparse->offset > t->entry_total) {

		LARGE_INTEGER distance;

		distance.QuadPart = t->current_sparse->offset;

		if (!SetFilePointerEx_perso(t->entry_fh, distance, NULL, FILE_BEGIN)) {

			DWORD lasterr;



			lasterr = GetLastError();

			if (lasterr == ERROR_ACCESS_DENIED)

				errno = EBADF;

			else

				la_dosmaperr(lasterr);

			archive_set_error(&a->archive, errno, "Seek error");

			r = ARCHIVE_FATAL;

			a->archive.state = ARCHIVE_STATE_FATAL;

			goto abort_read_data;

		}

		bytes = t->current_sparse->offset - t->entry_total;

		t->entry_remaining_bytes -= bytes;

		t->entry_total += bytes;

	}

	if (buffbytes > 0) {

		DWORD bytes_read;

		if (!ReadFile(t->entry_fh, t->entry_buff,

		    (uint32_t)buffbytes, &bytes_read, NULL)) {

			DWORD lasterr;



			lasterr = GetLastError();

			if (lasterr == ERROR_NO_DATA)

				errno = EAGAIN;

			else if (lasterr == ERROR_ACCESS_DENIED)

				errno = EBADF;

			else

				la_dosmaperr(lasterr);

			archive_set_error(&a->archive, errno, "Read error");

			r = ARCHIVE_FATAL;

			a->archive.state = ARCHIVE_STATE_FATAL;

			goto abort_read_data;

		}

		bytes = bytes_read;

	} else

		bytes = 0;

	if (bytes == 0) {

		/* Get EOF */

		t->entry_eof = 1;

		r = ARCHIVE_EOF;

		goto abort_read_data;

	}

	*buff = t->entry_buff;

	*size = bytes;

	*offset = t->entry_total;

	t->entry_total += bytes;

	t->entry_remaining_bytes -= bytes;

	if (t->entry_remaining_bytes == 0) {

		/* Close the current file descriptor */

		close_and_restore_time(t->entry_fh, t, &t->restore_time);

		t->entry_fh = INVALID_HANDLE_VALUE;

		t->entry_eof = 1;

	}

	t->current_sparse->offset += bytes;

	t->current_sparse->length -= bytes;

	if (t->current_sparse->length == 0 && !t->entry_eof)

		t->current_sparse++;

	return (ARCHIVE_OK);



abort_read_data:

	*buff = NULL;

	*size = 0;

	*offset = t->entry_total;

	if (t->entry_fh != INVALID_HANDLE_VALUE) {

		/* Close the current file descriptor */

		close_and_restore_time(t->entry_fh, t, &t->restore_time);

		t->entry_fh = INVALID_HANDLE_VALUE;

