	const struct archive_entry_header_ustar *header;
	const struct archive_entry_header_gnutar *gnuheader;

	tar_flush_unconsumed(a, unconsumed);

	/* Read 512-byte header record */
	h = __archive_read_ahead(a, 512, &bytes);
	if (bytes < 0)
		return ((int)bytes);
	if (bytes == 0) { /* EOF at a block boundary. */
		/* Some writers do omit the block of nulls. <sigh> */
		return (ARCHIVE_EOF);
	}
	if (bytes < 512) {  /* Short block at EOF; this is bad. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated tar archive");
		return (ARCHIVE_FATAL);
	}
	*unconsumed = 512;

	/* Check for end-of-archive mark. */
	if (h[0] == 0 && archive_block_is_null(h)) {
		/* Try to consume a second all-null record, as well. */
		tar_flush_unconsumed(a, unconsumed);
		h = __archive_read_ahead(a, 512, NULL);
		if (h != NULL)
			__archive_read_consume(a, 512);
		archive_clear_error(&a->archive);
		if (a->archive.archive_format_name == NULL) {
			a->archive.archive_format = ARCHIVE_FORMAT_TAR;
			a->archive.archive_format_name = "tar";
		}
		return (ARCHIVE_EOF);
	}

	/*
