{
		archive_set_error(&a->archive, EINVAL,
		    "Incorrect file header signature");
		return (ARCHIVE_WARN);
	}