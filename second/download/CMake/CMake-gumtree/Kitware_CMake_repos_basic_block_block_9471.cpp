(fstat(tempfd, &copyfile_stat)) {
		archive_set_error(&a->archive, errno,
		    "Could not check size of extended attributes");
		ret = ARCHIVE_WARN;
		goto cleanup;
	}