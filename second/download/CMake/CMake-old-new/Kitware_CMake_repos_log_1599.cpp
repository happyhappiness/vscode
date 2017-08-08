archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "%s can't be converted from %s to current locale.",
	    name, archive_string_conversion_charset_name(sconv));