{
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ENOMEM,
		    "Internal error initializing compression library");
		return (ARCHIVE_FATAL);
	}