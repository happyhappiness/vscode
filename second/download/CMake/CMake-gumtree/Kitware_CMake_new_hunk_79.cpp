		if (path == NULL)
			path = archive_entry_pathname(entry);
			
#ifdef _PC_MIN_HOLE_SIZE
		if (pathconf(path, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);
#endif
		*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
