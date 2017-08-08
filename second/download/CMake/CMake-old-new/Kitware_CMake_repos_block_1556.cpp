{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate lha data");
		return (ARCHIVE_FATAL);
	}