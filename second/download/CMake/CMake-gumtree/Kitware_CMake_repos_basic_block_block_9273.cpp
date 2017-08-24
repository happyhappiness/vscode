{
		archive_set_error(&a->archive, EINVAL,
		    "No reader function provided to archive_read_open");
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}