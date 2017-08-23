{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Missing type keyword in mtree specification");
		return (ARCHIVE_WARN);
	}