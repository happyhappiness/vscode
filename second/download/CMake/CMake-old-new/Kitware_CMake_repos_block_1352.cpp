{
		archive_set_error(&(a->archive), -1,
		    "Format must be set before you can write to an archive.");
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}