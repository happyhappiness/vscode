(ret < ARCHIVE_WARN) {
		archive_entry_free(entry_main);
		return (NULL);
	}