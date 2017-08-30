	}
	__archive_read_consume(a, filename_length);

	/* Work around a bug in Info-Zip: When reading from a pipe, it
	 * stats the pipe instead of synthesizing a file entry. */
	if ((zip_entry->mode & AE_IFMT) == AE_IFIFO) {
