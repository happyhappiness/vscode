{
		archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID too large");
		ret = ARCHIVE_FAILED;
	}