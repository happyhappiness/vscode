{
		warning_done = 1;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Cannot restore extended attributes on this system");
		return (ARCHIVE_WARN);
	}