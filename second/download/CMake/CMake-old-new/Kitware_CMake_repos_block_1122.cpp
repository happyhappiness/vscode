{
		archive_set_error(&a->archive, ENOMEM,
			"No memory.");
		return ARCHIVE_FATAL;
	}