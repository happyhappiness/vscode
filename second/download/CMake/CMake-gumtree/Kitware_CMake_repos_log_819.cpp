archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
				"Decompression failed(%d)",
			    r);