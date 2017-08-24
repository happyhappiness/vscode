{
		archive_set_error(&a->archive, errno,
		    "Failed to read a restoring file");
		close(fd);
		ret = ARCHIVE_WARN;
		goto skip_appledouble;
	}