int
archive_read_support_format_raw(struct archive *_a)
{
	struct raw_info *info;
	struct archive_read *a = (struct archive_read *)_a;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_raw");

	info = (struct raw_info *)calloc(1, sizeof(*info));
	if (info == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate raw_info data");
		return (ARCHIVE_FATAL);
	}

	r = __archive_read_register_format(a,
	    info,
	    "raw",
	    archive_read_format_raw_bid,
	    NULL,
	    archive_read_format_raw_read_header,
	    archive_read_format_raw_read_data,
	    archive_read_format_raw_read_data_skip,
	    NULL,
	    archive_read_format_raw_cleanup,
	    NULL,
	    NULL);
	if (r != ARCHIVE_OK)
		free(info);
	return (r);
}