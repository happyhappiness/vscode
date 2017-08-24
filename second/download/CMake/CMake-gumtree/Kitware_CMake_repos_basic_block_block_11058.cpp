{
	struct archive_read *a = (struct archive_read *)_a;
	struct cab *cab;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_cab");

	cab = (struct cab *)calloc(1, sizeof(*cab));
	if (cab == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate CAB data");
		return (ARCHIVE_FATAL);
	}
	archive_string_init(&cab->ws);
	archive_wstring_ensure(&cab->ws, 256);

	r = __archive_read_register_format(a,
	    cab,
	    "cab",
	    archive_read_format_cab_bid,
	    archive_read_format_cab_options,
	    archive_read_format_cab_read_header,
	    archive_read_format_cab_read_data,
	    archive_read_format_cab_read_data_skip,
	    NULL,
	    archive_read_format_cab_cleanup,
	    NULL,
	    NULL);

	if (r != ARCHIVE_OK)
		free(cab);
	return (ARCHIVE_OK);
}