	}

	/* Fail if we can't make our buffer big enough. */
	if (archive_string_ensure(as, size+1) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory");
		return (ARCHIVE_FATAL);
