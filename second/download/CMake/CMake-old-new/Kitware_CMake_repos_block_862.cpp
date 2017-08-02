{
		archive_set_error(&a->archive, errno,
		    "Could not open extended attribute file");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}