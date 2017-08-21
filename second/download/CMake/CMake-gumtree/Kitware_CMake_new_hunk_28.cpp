	path = NULL;

	if (*fd < 0) {
		path = archive_read_disk_entry_setup_path(a, entry, fd);
		if (path == NULL)
			return (ARCHIVE_WARN);
	}

	if (*fd >= 0)
