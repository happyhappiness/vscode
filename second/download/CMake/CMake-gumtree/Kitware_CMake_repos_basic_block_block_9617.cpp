((list = malloc(list_size)) == NULL) {
		archive_set_error(&a->archive, errno, "Out of memory");
		return (ARCHIVE_FATAL);
	}