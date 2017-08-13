{
		free(zip);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate compression buffer");
		return (ARCHIVE_FATAL);
	}