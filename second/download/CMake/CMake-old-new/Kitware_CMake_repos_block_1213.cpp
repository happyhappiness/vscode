{
		archive_set_error(&a->archive, errno, "statfs failed");
		return (ARCHIVE_FAILED);
	}