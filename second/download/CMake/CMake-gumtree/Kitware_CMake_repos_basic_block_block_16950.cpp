(__archive_write_format_header_ustar(a, ustarbuff, entry_main, -1, 0,
	    NULL) == ARCHIVE_FATAL)
		return (ARCHIVE_FATAL);