{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Found entry with empty filename");
		return (ARCHIVE_FATAL);
	}