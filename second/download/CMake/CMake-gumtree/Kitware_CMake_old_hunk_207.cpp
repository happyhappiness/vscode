	if (a->format_free != NULL)

		(a->format_free)(a);



	cpio = (struct cpio *)malloc(sizeof(*cpio));

	if (cpio == NULL) {

		archive_set_error(&a->archive, ENOMEM, "Can't allocate cpio data");

		return (ARCHIVE_FATAL);

	}

	memset(cpio, 0, sizeof(*cpio));

	a->format_data = cpio;

	a->format_name = "cpio";

	a->format_options = archive_write_newc_options;

