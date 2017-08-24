(a->filesize == 0 || a->fd < 0) {
		archive_set_error(&a->archive, 0,
		    "Attempt to write to an empty file");
		return (ARCHIVE_WARN);
	}