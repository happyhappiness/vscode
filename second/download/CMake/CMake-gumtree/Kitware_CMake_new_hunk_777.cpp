
	/* If this is a symlink, read the link contents. */
	if (archive_entry_filetype(entry) == AE_IFLNK) {
		h = __archive_read_ahead(a,
			(size_t)cpio->entry_bytes_remaining, NULL);
		if (h == NULL)
			return (ARCHIVE_FATAL);
		if (archive_entry_copy_symlink_l(entry, (const char *)h,
		    (size_t)cpio->entry_bytes_remaining, sconv) != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
