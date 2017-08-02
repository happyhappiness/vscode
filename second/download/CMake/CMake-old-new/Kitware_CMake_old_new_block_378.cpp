{
		archive_set_error(f->archive, EINVAL,
		    "Can't initialise filter");
		return (ARCHIVE_FATAL);
	}