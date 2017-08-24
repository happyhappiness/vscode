(*fd < 0) {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
		if (a->tree != NULL)
			*fd = a->open_on_current_dir(a->tree, path,
				O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		else
			*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
		__archive_ensure_cloexec_flag(*fd);
	}