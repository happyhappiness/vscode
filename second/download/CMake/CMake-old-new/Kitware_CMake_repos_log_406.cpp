archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "lzma compression failed:"
		    " lzma_code() call returned status %d", r)