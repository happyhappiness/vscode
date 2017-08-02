archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Bzip2 compression failed:"
		    " BZ2_bzCompress() call returned status %d", r)