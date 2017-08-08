archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlTextWriterEndDocument() failed: %d", r);