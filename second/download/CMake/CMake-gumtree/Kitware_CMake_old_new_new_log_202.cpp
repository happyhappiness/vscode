archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT, "%s %s %s",
		    "Can't translate ", attr, " to UTF-8");