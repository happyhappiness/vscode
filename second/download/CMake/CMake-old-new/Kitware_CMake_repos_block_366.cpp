{
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for b64encode filter");
		return (ARCHIVE_FATAL);
	}