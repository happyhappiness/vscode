	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_warc");

	if ((w = malloc(sizeof(*w))) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate warc data");
		return (ARCHIVE_FATAL);
	}
	memset(w, 0, sizeof(*w));

	r = __archive_read_register_format(
		a, w, "warc",
