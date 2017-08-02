archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s", path,
		    archive_string_conversion_charset_name(sconv))