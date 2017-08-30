	 * and are not terminated in '/', so we don't trim anything
	 * that starts with '/'.)
	 */
	if (filename[0] != '/' && p > filename && *p == '/') {
		*p = '\0';
	}

	if (p < filename) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Found entry with empty filename");
		return (ARCHIVE_FATAL);
	}

	/*
	 * '//' is the GNU filename table.
