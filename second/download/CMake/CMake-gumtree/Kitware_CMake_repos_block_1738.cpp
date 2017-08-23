{
		r = get_entry_uname(a, entry_main, &uname, &uname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate uname '%s' to %s", uname,
		    archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
		sconv = NULL;/* The header charset switches to binary mode. */
	}