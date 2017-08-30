	}

	__archive_read_consume(a, filename_length);



	/* Read the extra data. */

	if ((h = __archive_read_ahead(a, extra_length, NULL)) == NULL) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

		    "Truncated ZIP file header");

		return (ARCHIVE_FATAL);

	}



	process_extra(h, extra_length, zip_entry);

	__archive_read_consume(a, extra_length);



	/* Work around a bug in Info-Zip: When reading from a pipe, it

	 * stats the pipe instead of synthesizing a file entry. */

	if ((zip_entry->mode & AE_IFMT) == AE_IFIFO) {

