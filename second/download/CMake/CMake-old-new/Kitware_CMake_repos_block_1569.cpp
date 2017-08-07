{
		archive_set_error(&a->archive, EINVAL,
		    "Special header too large");
		return (ARCHIVE_FATAL);
	}