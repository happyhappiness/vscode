archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported encryption format version: %u",
		    archive_le16dec(p+4))