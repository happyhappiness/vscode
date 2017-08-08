{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for metadata(xattr)");
		ret = ARCHIVE_FATAL;
		goto exit_xattr;
	}