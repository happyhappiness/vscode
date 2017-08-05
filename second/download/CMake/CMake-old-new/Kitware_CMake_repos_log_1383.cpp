archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate gname '%s' to %s",
		    archive_entry_gname(entry),
		    archive_string_conversion_charset_name(sconv));