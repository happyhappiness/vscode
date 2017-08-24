(*fd < 0 && a->tree != NULL) {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
		*fd = a->open_on_current_dir(a->tree, path,
				O_RDONLY | O_NONBLOCK);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
	}