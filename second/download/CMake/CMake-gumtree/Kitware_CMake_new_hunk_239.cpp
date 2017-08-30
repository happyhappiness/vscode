	archive_check_magic(_a, ARCHIVE_READ_MAGIC,

	    ARCHIVE_STATE_NEW, "archive_read_support_format_ar");



	ar = (struct ar *)calloc(1, sizeof(*ar));

	if (ar == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate ar data");

		return (ARCHIVE_FATAL);

	}

	ar->strtab = NULL;



	r = __archive_read_register_format(a,

