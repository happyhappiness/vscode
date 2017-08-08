{
		free(value);
		archive_set_error(&a->archive, errno,
		    "Couldn't read extended attribute");
		return (ARCHIVE_WARN);
	}