{
		free(file);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for Name");
		return (ARCHIVE_FATAL);
	}