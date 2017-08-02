{
		archive_set_error(&a->archive, errno,
			"Could not check extended attributes");
		return (ARCHIVE_WARN);
	}