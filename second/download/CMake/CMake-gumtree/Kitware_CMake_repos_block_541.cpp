{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate raw_info data");
		return (ARCHIVE_FATAL);
	}