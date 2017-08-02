archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "ZIP decompression failed (%d)", r)