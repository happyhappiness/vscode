{
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathame");
			ret = ARCHIVE_FATAL;
			goto exit_write_header;
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s",
		    archive_entry_pathname(entry),
		    archive_string_conversion_charset_name(sconv));
		ret2 = ARCHIVE_WARN;
	}