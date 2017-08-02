{
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for bzip2 stream");
		return (ARCHIVE_FATAL);
	}