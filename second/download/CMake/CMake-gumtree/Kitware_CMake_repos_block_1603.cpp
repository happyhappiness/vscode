{
		tar->entry_bytes_remaining = 0;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Tar entry has negative size");
		return (ARCHIVE_FATAL);
	}