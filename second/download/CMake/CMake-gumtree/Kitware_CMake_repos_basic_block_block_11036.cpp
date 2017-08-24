{
	struct ar *ar = (struct ar*)(a->format->data);
	size_t unconsumed;
	const void *header_data;
	int ret;

	if (!ar->read_global_header) {
		/*
		 * We are now at the beginning of the archive,
		 * so we need first consume the ar global header.
		 */
		__archive_read_consume(a, 8);
		ar->read_global_header = 1;
		/* Set a default format code for now. */
		a->archive.archive_format = ARCHIVE_FORMAT_AR;
	}

	/* Read the header for the next file entry. */
	if ((header_data = __archive_read_ahead(a, 60, NULL)) == NULL)
		/* Broken header. */
		return (ARCHIVE_EOF);
	
	unconsumed = 60;
	
	ret = _ar_read_header(a, entry, ar, (const char *)header_data, &unconsumed);

	if (unconsumed)
		__archive_read_consume(a, unconsumed);

	return ret;
}