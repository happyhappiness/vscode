static int
archive_write_set_format_ar(struct archive_write *a)
{
	struct ar_w *ar;

	/* If someone else was already registered, unregister them. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	ar = (struct ar_w *)calloc(1, sizeof(*ar));
	if (ar == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Can't allocate ar data");
		return (ARCHIVE_FATAL);
	}
	a->format_data = ar;

	a->format_name = "ar";
	a->format_write_header = archive_write_ar_header;
	a->format_write_data = archive_write_ar_data;
	a->format_close = archive_write_ar_close;
	a->format_free = archive_write_ar_free;
	a->format_finish_entry = archive_write_ar_finish_entry;
	return (ARCHIVE_OK);
}