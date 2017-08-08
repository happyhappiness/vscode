{
		archive_set_error(&a->archive, ENOMEM, "Can't allocate raw data");
		return (ARCHIVE_FATAL);
	}