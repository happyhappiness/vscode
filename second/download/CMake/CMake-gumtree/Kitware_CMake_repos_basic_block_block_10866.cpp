{
		if (errno == ENOMEM)
			archive_set_error(&a->archive, -1,
			    "Couldn't allocate memory");
		else
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
		return (ARCHIVE_FATAL);
	}