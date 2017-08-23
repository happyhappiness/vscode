{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Directory is beyond end-of-media: %s",
		    parent->name.s);
		return (ARCHIVE_WARN);
	}