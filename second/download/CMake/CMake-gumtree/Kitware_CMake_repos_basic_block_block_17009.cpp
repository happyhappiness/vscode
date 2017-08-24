(r != ARCHIVE_OK) {
		r = get_entry_pathname(a, entry_main, &path,
		    &path_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s", path,
		    archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
		sconv = NULL;/* The header charset switches to binary mode. */
	}