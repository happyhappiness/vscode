(archive_string_ensure(as, (size_t)size+1) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory");
		return (ARCHIVE_FATAL);
	}