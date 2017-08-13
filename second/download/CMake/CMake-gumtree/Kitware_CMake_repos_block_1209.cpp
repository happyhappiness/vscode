{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate tar data");
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}