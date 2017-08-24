(*fd >= 0) {
#ifdef _PC_MIN_HOLE_SIZE
		if (fpathconf(*fd, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);
#endif
		initial_off = lseek(*fd, 0, SEEK_CUR);
		if (initial_off != 0)
			lseek(*fd, 0, SEEK_SET);
	} else {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
			
#ifdef _PC_MIN_HOLE_SIZE
		if (pathconf(path, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);
#endif
		*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
		__archive_ensure_cloexec_flag(*fd);
		initial_off = 0;
	}