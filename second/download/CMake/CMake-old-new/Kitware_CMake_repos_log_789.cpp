archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Unknown codec ID: %lX", zip->codec)