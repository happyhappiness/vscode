int
archive_write_set_format_raw(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct raw *raw;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_raw");

	/* If someone else was already registered, unregister them. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	raw = (struct raw *)calloc(1, sizeof(*raw));
	if (raw == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Can't allocate raw data");
		return (ARCHIVE_FATAL);
	}
	raw->entries_written = 0;
	a->format_data = raw;
	a->format_name = "raw";
        /* no options exist for this format */
	a->format_options = NULL;
	a->format_write_header = archive_write_raw_header;
	a->format_write_data = archive_write_raw_data;
	a->format_finish_entry = NULL;
        /* nothing needs to be done on closing */
	a->format_close = NULL;
	a->format_free = archive_write_raw_free;
	a->archive.archive_format = ARCHIVE_FORMAT_RAW;
	a->archive.archive_format_name = "RAW";
	return (ARCHIVE_OK);
}