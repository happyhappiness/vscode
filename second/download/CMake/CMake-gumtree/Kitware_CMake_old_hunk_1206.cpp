
	/* Entries other than a regular file or a folder are skipped. */
	type = archive_entry_filetype(entry);
	if ((type != AE_IFREG) & (type != AE_IFDIR)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Filetype not supported");
		return ARCHIVE_FAILED;
