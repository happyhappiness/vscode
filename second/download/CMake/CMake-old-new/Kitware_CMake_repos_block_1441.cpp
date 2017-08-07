{
		archive_set_error(&a->archive, EINVAL,
		    "Can't get a wide character version of the path");
		return (ARCHIVE_FAILED);
	}