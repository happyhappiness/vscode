{
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM, "%s %s",
			    "Can't allocate memory for ", attr);
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT, "%s %s %s",
		    "Can't translate ", attr, " to UTF-8");
		return(ARCHIVE_WARN);
	}