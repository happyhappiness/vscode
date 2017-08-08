{
		archive_set_error(&a->archive, errno,
		    "Failed to remove resource fork");
		return (ARCHIVE_WARN);
	}