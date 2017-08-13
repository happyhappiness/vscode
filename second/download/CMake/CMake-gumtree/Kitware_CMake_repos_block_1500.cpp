{
		/* Reject filenames with trailing "/" */
		archive_set_error(&a->archive, EINVAL,
		    "Invalid filename");
		return (ARCHIVE_WARN);
	}