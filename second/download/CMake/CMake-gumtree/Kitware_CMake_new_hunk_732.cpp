	archive_string_init(&path);
	if (archive_string_append_from_wcs(&path, pathname,
	    wcslen(pathname)) != 0) {
		if (errno == ENOMEM)
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
		else
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't convert a path to a char string");
		a->archive.state = ARCHIVE_STATE_FATAL;
		ret = ARCHIVE_FATAL;
	} else
