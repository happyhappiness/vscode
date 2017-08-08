{
		r = get_entry_gname(a, entry_main, &gname, &gname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate gname '%s' to %s", gname,
		    archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
		sconv = NULL;/* The header charset switches to binary mode. */
	}