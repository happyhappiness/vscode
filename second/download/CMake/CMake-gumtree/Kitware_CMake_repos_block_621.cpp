{
	if (a->pst != NULL) {
		/* Already have stat() data available. */
		return (ARCHIVE_OK);
	}
	if (a->fh != INVALID_HANDLE_VALUE &&
	    GetFileInformationByHandle(a->fh, &a->st) == 0) {
		a->pst = &a->st;
		return (ARCHIVE_OK);
	}

	/*
	 * XXX At this point, symlinks should not be hit, otherwise
	 * XXX a race occurred.  Do we want to check explicitly for that?
	 */
	if (file_information(a, a->name, &a->st, NULL, 1) == 0) {
		a->pst = &a->st;
		return (ARCHIVE_OK);
	}
	archive_set_error(&a->archive, errno, "Couldn't stat file");
	return (ARCHIVE_WARN);
}