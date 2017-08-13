		bytes_to_write = size;
		/* Seek if necessary to the specified offset. */
		if (a->offset < a->fd_offset) {
			/* Can't support backword move. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Seek failed");
			return (ARCHIVE_FATAL);
