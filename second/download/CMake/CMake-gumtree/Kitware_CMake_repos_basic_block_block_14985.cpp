(errno != ENOENT && errno != ENOTDIR) {
		/* Stat failed? */
		archive_set_error(&a->archive, errno,
		    "Can't test directory '%s'", path);
		return (ARCHIVE_FAILED);
	}