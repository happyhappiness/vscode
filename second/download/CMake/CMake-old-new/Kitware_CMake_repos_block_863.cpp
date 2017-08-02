{
		archive_set_error(&a->archive, errno,
		    "Could not pack extended attributes");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}