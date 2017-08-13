{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate gnutar data");
		return (ARCHIVE_FATAL);
	}