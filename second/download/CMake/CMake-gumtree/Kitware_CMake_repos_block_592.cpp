{
		/* no good */
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Bad record header");
		return (ARCHIVE_FATAL);
	}