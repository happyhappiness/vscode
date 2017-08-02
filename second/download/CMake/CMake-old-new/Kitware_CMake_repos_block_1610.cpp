{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Multivolume cabinet file is unsupported");
		return (ARCHIVE_WARN);
	}