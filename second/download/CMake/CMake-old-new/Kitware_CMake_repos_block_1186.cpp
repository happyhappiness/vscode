{
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC, "Buffer overflow");
		return (ARCHIVE_FATAL);
	}