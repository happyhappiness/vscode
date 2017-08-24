{
	struct archive_write *a = (struct archive_write *)_a;
	struct gnutar *gnutar;

	gnutar = (struct gnutar *)calloc(1, sizeof(*gnutar));
	if (gnutar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate gnutar data");
		return (ARCHIVE_FATAL);
	}
	a->format_data = gnutar;
	a->format_name = "gnutar";
	a->format_options = archive_write_gnutar_options;
	a->format_write_header = archive_write_gnutar_header;
	a->format_write_data = archive_write_gnutar_data;
	a->format_close = archive_write_gnutar_close;
	a->format_free = archive_write_gnutar_free;
	a->format_finish_entry = archive_write_gnutar_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_TAR_GNUTAR;
	a->archive.archive_format_name = "GNU tar";
	return (ARCHIVE_OK);
}