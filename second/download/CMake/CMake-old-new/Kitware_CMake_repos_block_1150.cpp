{
		archive_set_error(&a->archive, EINVAL,
			"Invalid index specified.");
		return ARCHIVE_FATAL;
	}