{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Internal error: "
		    "No format->read_data function registered");
		return (ARCHIVE_FATAL);
	}