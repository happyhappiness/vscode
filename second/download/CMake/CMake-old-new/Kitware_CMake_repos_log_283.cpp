archive_set_error(&a->archive,
			    (r < 0)?errno:ARCHIVE_ERRNO_MISC,
			    "Failed to read resource fork")