{
		archive_set_error(&a->archive, ERANGE,
		    "File modification time too large");
		return (ARCHIVE_WARN);
	}