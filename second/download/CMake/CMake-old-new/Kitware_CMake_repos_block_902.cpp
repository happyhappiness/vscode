{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate xar data");
		return (ARCHIVE_FATAL);
	}