{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "TOC uncompressed size error");
		return (ARCHIVE_FATAL);
	}