{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			"Couldn't allocate memory");
		exit_sts = ARCHIVE_FATAL;
		goto exit_setup_sparse;
	}