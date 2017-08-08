{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for %s", name);
		return (ARCHIVE_FATAL);
	}