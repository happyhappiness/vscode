{
		archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID too large");
		return (ARCHIVE_WARN);
	}