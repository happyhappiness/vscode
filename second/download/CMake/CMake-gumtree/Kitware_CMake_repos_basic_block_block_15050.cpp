{
		archive_set_error(&a->archive, errno,
		    "Failed to open a restoring file");
		ret = ARCHIVE_WARN;
		goto skip_appledouble;
	}