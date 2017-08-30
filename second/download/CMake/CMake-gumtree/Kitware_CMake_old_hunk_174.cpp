	if (tar->entry_bytes_remaining < 0) {

		tar->entry_bytes_remaining = 0;

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Tar entry has negative size?");

		err = ARCHIVE_WARN;

	}

	tar->realsize = tar->entry_bytes_remaining;

	archive_entry_set_size(entry, tar->entry_bytes_remaining);

