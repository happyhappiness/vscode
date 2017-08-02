archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Unexpected codec ID: %lX", zip->codec2)