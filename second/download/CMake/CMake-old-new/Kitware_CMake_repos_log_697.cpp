archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Too many directories(%d) over 65535.", dir_number)