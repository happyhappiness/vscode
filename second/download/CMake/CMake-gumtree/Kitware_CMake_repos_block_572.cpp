{
		archive_set_error(a,
		    ENOMEM, "Out of memory adding file to list");
		return (ARCHIVE_FATAL);
	}