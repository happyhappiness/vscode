{
		archive_set_error(&a->archive, errno,
		    "Boot file(%jd) is too small", (intmax_t)size + 64);
		return (ARCHIVE_FATAL);
	}