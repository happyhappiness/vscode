{
		archive_set_error(&a->archive, errno,
		    "Failed to read metadata(xattr)");
		ret = ARCHIVE_WARN;
		goto exit_xattr;
	}