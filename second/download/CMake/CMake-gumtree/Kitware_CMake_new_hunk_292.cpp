	if (a->format_free != NULL)

		(a->format_free)(a);



	pax = (struct pax *)calloc(1, sizeof(*pax));

	if (pax == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate pax data");

		return (ARCHIVE_FATAL);

	}

	pax->flags = WRITE_LIBARCHIVE_XATTR | WRITE_SCHILY_XATTR;



	a->format_data = pax;

	a->format_name = "pax";

	a->format_options = archive_write_pax_options;

