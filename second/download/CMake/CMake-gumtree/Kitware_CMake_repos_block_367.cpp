{
		archive_set_error(&a->archive, errno,
		    "Can't set file flags on symlink.");
		return (ARCHIVE_WARN);
	}