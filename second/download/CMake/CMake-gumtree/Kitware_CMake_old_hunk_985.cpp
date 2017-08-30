	if (zip->zip_entries == NULL) {
		zip->zip_entries = malloc(sizeof(struct zip_entry));
		if (zip->zip_entries == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Out  of memory");
			return ARCHIVE_FATAL;
		}
	}
	zip->entry = zip->zip_entries;
	memset(zip->entry, 0, sizeof(struct zip_entry));

	/* Search ahead for the next local file header. */
	__archive_read_consume(a, zip->unconsumed);
	zip->unconsumed = 0;
	for (;;) {
		int64_t skipped = 0;
