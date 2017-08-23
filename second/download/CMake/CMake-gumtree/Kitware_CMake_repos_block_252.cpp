{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Truncated archive file");
		return (ARCHIVE_FATAL);
	}