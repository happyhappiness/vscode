{
		free(data);
		archive_set_error(_a, ARCHIVE_ERRNO_MISC,
		    "lzo_init(type check) failed");
		return (ARCHIVE_FATAL);
	}