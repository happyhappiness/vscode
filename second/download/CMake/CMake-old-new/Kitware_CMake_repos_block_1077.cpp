{
		archive_set_error(&(a->archive), EINVAL, "pathname is empty");
		return (ARCHIVE_FAILED);
	}