{
		archive_set_error(&a->archive, errno,
			"Couldn't retrieve extended attributes");
		free(list);
		return (ARCHIVE_WARN);
	}