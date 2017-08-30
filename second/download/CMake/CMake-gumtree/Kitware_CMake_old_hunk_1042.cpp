	outranges_size = 2048;

	outranges = (FILE_ALLOCATED_RANGE_BUFFER *)malloc(outranges_size);

	if (outranges == NULL) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			"Couldn't allocate memory");

		exit_sts = ARCHIVE_FATAL;

		goto exit_setup_sparse;

