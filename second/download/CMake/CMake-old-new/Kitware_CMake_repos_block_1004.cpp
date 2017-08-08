{
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library");
		return (ARCHIVE_FATAL);
	}