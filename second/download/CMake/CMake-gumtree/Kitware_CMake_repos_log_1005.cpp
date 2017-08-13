archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "GZip compression failed:"
		    " deflate() call returned status %d", r);