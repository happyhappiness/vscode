{
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Pathname can't be converted from %s to current locale.",
		    archive_string_conversion_charset_name(sconv));
		r = ARCHIVE_WARN;
	}