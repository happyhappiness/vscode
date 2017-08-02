{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Internal error: "
		    "No format_seek_data_block function registered");
		return (ARCHIVE_FATAL);
	}