{
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for compression");
		return (ARCHIVE_FATAL);
	}