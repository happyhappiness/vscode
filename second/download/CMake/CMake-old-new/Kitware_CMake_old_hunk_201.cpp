	if (a->format_free != NULL)
		(a->format_free)(a);

	pax = (struct pax *)malloc(sizeof(*pax));
	if (pax == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate pax data");
		return (ARCHIVE_FATAL);
	}
	memset(pax, 0, sizeof(*pax));
	a->format_data = pax;
	a->format_name = "pax";
	a->format_options = archive_write_pax_options;
