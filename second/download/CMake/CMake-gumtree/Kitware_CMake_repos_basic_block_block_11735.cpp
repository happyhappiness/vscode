{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid length of directory record");
		return (NULL);
	}