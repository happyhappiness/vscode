archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC,
		    "xmlNewTextWriterMemory() "
		    "couldn't create xml writer");