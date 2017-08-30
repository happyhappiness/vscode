	archive_string_init(&wpath);
	if (archive_wstring_append_from_mbs(&wpath, pathname,
	    strlen(pathname)) != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't convert a path to a wchar_t string");
		a->archive.state = ARCHIVE_STATE_FATAL;
		ret = ARCHIVE_FATAL;
	} else
