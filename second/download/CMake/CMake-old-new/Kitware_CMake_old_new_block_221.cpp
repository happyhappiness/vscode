{
		archive_set_error(&a->archive, 0,
		    "Write request too large");
		return (ARCHIVE_WARN);
	}