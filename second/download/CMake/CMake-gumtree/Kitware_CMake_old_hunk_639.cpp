	    ARCHIVE_STATE_NEW, "archive_read_support_format_tar");

	tar = (struct tar *)calloc(1, sizeof(*tar));
	if (tar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate tar data");
