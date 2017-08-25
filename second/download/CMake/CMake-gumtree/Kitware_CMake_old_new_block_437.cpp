{
		archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Malformed device attribute");
		return (ARCHIVE_WARN);
	}