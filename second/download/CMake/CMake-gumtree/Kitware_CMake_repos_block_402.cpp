{
		free(data);
		archive_set_error(_a, ENOMEM, "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}