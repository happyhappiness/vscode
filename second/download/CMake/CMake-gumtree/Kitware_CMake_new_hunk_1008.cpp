		return (ARCHIVE_OK);

	/* Does filesystem support the reporting of hole ? */
	if (*fd < 0 && a->tree != NULL) {
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

	if (*fd >= 0) {
		if (fpathconf(*fd, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);
		initial_off = lseek(*fd, 0, SEEK_CUR);
		if (initial_off != 0)
			lseek(*fd, 0, SEEK_SET);
	} else {
		const char *path;

		path = archive_entry_sourcepath(entry);
		if (path == NULL)
			path = archive_entry_pathname(entry);
			
		if (pathconf(path, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);
		*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		if (*fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't open `%s'", path);
			return (ARCHIVE_FAILED);
		}
		__archive_ensure_cloexec_flag(*fd);
		initial_off = 0;
	}

	off_s = 0;
	size = archive_entry_size(entry);
	while (off_s < size) {
		off_s = lseek(*fd, off_s, SEEK_DATA);
		if (off_s == (off_t)-1) {
			if (errno == ENXIO)
				break;/* no more hole */
