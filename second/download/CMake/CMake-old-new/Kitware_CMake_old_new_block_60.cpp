{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate directory traversal data");
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}