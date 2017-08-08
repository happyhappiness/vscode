{
		free(f);
		archive_set_error(&(a->archive), EINVAL, "pathname is NULL");
		return (ARCHIVE_FAILED);
	}