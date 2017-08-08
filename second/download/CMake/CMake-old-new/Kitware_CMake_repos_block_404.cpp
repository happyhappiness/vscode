{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate 7-Zip data");
		return (ARCHIVE_FATAL);
	}