archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterStartDocument() failed: %d", r)