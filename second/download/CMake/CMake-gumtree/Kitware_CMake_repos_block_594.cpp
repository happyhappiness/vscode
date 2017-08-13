{
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Invalid record version");
		return (ARCHIVE_FATAL);
	}