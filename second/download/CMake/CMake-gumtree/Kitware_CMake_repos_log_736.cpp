archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Compression failed:"
				    " deflate() call returned status %d",
				    r);