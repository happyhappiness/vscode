(archive_string_append_from_wcs(&path, pathname,
	    wcslen(pathname)) != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't convert a path to a char string");
		a->archive.state = ARCHIVE_STATE_FATAL;
		ret = ARCHIVE_FATAL;
	} else
		ret = _archive_read_disk_open(_a, path.s)