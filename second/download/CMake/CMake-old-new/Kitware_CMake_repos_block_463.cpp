{
		archive_set_error(&a->archive, errno, "Can't read");
		return (ARCHIVE_WARN);
	}