{
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for uuencode filter");
		return (ARCHIVE_FATAL);
	}