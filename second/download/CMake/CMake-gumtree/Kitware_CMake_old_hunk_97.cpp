			    "Rejecting malformed cpio archive: symlink contents exceed 1 megabyte");
			return (ARCHIVE_FATAL);
		}
		h = __archive_read_ahead(a,
			(size_t)cpio->entry_bytes_remaining, NULL);
		if (h == NULL)
			return (ARCHIVE_FATAL);
		if (archive_entry_copy_symlink_l(entry, (const char *)h,
		    (size_t)cpio->entry_bytes_remaining, sconv) != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
