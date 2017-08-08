{
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Failed to clean up compressor");
		return (ARCHIVE_FATAL);
	}