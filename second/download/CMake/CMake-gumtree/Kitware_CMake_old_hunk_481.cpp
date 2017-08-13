	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_zip");

	zip = (struct zip *)malloc(sizeof(*zip));
	if (zip == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip data");
		return (ARCHIVE_FATAL);
	}
	memset(zip, 0, sizeof(*zip));

	/* Streamable reader doesn't support mac extensions. */
	zip->process_mac_extensions = 0;
