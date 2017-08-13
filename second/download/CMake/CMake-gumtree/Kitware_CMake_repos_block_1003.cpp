{
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for gzip stream");
		return (ARCHIVE_FATAL);
	}