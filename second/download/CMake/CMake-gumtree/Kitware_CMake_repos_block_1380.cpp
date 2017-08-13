{
		free(state);
		free(buffer);
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for output buffering");
		return (ARCHIVE_FATAL);
	}