		/* Grab a bunch of bytes. */

		buff = __archive_read_ahead(a, 1, &bytes_avail);

		if (bytes_avail <= 0) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

			    "Truncated ZIP file data");

			return (ARCHIVE_FATAL);

		}

		if (bytes_avail > zip->entry_bytes_remaining)

			bytes_avail = zip->entry_bytes_remaining;

	}

	*size = bytes_avail;

	zip->entry_bytes_remaining -= bytes_avail;

