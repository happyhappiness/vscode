{
		archive_set_error(&(a->archive), EINVAL, "pattern is empty");
		return (ARCHIVE_FAILED);
	}