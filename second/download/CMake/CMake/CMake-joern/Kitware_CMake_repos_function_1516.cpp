int
archive_write_set_format_warc(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct warc_s *w;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_warc");

	/* If another format was already registered, unregister it. */
	if (a->format_free != NULL) {
		(a->format_free)(a);
	}

	w = malloc(sizeof(*w));
	if (w == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate warc data");
		return (ARCHIVE_FATAL);
	}
	/* by default we're emitting a file wide header */
	w->omit_warcinfo = 0U;
	/* obtain current time for date fields */
	w->now = time(NULL);
	/* reset file type info */
	w->typ = 0;
	/* also initialise our rng */
	w->rng = (unsigned int)w->now;

	a->format_data = w;
	a->format_name = "WARC/1.0";
	a->format_options = _warc_options;
	a->format_write_header = _warc_header;
	a->format_write_data = _warc_data;
	a->format_close = _warc_close;
	a->format_free = _warc_free;
	a->format_finish_entry = _warc_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_WARC;
	a->archive.archive_format_name = "WARC/1.0";
	return (ARCHIVE_OK);
}