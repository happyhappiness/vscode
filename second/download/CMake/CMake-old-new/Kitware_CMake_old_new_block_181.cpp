{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate v7tar data");
		return (ARCHIVE_FATAL);
	}