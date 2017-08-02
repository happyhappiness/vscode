{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate ustar data");
		return (ARCHIVE_FATAL);
	}