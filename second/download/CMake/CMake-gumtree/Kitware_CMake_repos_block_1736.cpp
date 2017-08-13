{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate pax data");
		return(ARCHIVE_FATAL);
	}