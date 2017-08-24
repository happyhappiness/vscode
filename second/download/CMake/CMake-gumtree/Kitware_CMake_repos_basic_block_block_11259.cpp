{
	struct cab *cab;
	int64_t bytes_skipped;
	int r;

	cab = (struct cab *)(a->format->data);

	if (cab->end_of_archive)
		return (ARCHIVE_EOF);

	if (!cab->read_data_invoked) {
		cab->bytes_skipped += cab->entry_bytes_remaining;
		cab->entry_bytes_remaining = 0;
		/* This entry is finished and done. */
		cab->end_of_entry_cleanup = cab->end_of_entry = 1;
		return (ARCHIVE_OK);
	}

	if (cab->entry_unconsumed) {
		/* Consume as much as the compressor actually used. */
		r = (int)cab_consume_cfdata(a, cab->entry_unconsumed);
		cab->entry_unconsumed = 0;
		if (r < 0)
			return (r);
	} else if (cab->entry_cfdata == NULL) {
		r = cab_next_cfdata(a);
		if (r < 0)
			return (r);
	}

	/* if we've already read to end of data, we're done. */
	if (cab->end_of_entry_cleanup)
		return (ARCHIVE_OK);

	/*
	 * If the length is at the beginning, we can skip the
	 * compressed data much more quickly.
	 */
	bytes_skipped = cab_consume_cfdata(a, cab->entry_bytes_remaining);
	if (bytes_skipped < 0)
		return (ARCHIVE_FATAL);

	/* If the compression type is none(uncompressed), we've already
	 * consumed data as much as the current entry size. */
	if (cab->entry_cffolder->comptype == COMPTYPE_NONE &&
	    cab->entry_cfdata != NULL)
		cab->entry_cfdata->unconsumed = 0;

	/* This entry is finished and done. */
	cab->end_of_entry_cleanup = cab->end_of_entry = 1;
	return (ARCHIVE_OK);
}