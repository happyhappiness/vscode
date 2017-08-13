	const char *path;
	ssize_t list_size;

	path = NULL;

	if (*fd < 0) {
		path = archive_entry_sourcepath(entry);
		if (path == NULL || (a->tree != NULL &&
		    a->tree_enter_working_dir(a->tree) != 0))
			path = archive_entry_pathname(entry);
		if (path == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Couldn't determine file path to read "
			    "extended attributes");
			return (ARCHIVE_WARN);
		}
		if (a->tree != NULL && (a->follow_symlinks ||
		    archive_entry_filetype(entry) != AE_IFLNK)) {
			*fd = a->open_on_current_dir(a->tree,
			    path, O_RDONLY | O_NONBLOCK);
		}
	}

