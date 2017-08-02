archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate linkname '%s' to %s", hardlink,
		    archive_string_conversion_charset_name(sconv))