{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid offset of CFFILE %jd < %jd",
		    (intmax_t)hd->files_offset, (intmax_t)cab->cab_offset);
		return (ARCHIVE_FATAL);
	}