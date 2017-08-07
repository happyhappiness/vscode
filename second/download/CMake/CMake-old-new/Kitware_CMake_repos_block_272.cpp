{
		archive_set_error(&a->archive,
		    ENOMEM, "Out of memory adding file to list");
		return (ARCHIVE_FATAL);
	}