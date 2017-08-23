	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_zip");

	zip = (struct zip *)calloc(1, sizeof(*zip));
	if (zip == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip data");
		return (ARCHIVE_FATAL);
	}

	/* Streamable reader doesn't support mac extensions. */
	zip->process_mac_extensions = 0;
