archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "lzmadec decompression failed(%d)",
			    r);