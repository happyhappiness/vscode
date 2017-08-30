		tempdir = getenv("TMPDIR");

	if (tempdir == NULL)

		tempdir = _PATH_TMP;

	tempfile = tempnam(tempdir, "tar.md.");



	/* XXX I wish copyfile() could pack directly to a memory

	 * buffer; that would avoid the temp file here.  For that

	 * matter, it would be nice if fcopyfile() actually worked,

	 * that would reduce the many open/close races here. */

	if (copyfile(name, tempfile, 0, copyfile_flags | COPYFILE_PACK)) {

		archive_set_error(&a->archive, errno,

		    "Could not pack extended attributes");

		ret = ARCHIVE_WARN;

		goto cleanup;

	}

	tempfd = open(tempfile, O_RDONLY);

	if (tempfd < 0) {

		archive_set_error(&a->archive, errno,

		    "Could not open extended attribute file");

		ret = ARCHIVE_WARN;

		goto cleanup;

	}

	if (fstat(tempfd, &copyfile_stat)) {

		archive_set_error(&a->archive, errno,

		    "Could not check size of extended attributes");

