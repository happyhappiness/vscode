	if (tar->entry_bytes_remaining < 0) {

		tar->entry_bytes_remaining = 0;

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Tar entry has negative size");

		return (ARCHIVE_FATAL);

	}

	if (tar->entry_bytes_remaining == INT64_MAX) {

		/* Note: tar_atol returns INT64_MAX on overflow */

		tar->entry_bytes_remaining = 0;

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Tar entry size overflow");

		return (ARCHIVE_FATAL);

	}

	tar->realsize = tar->entry_bytes_remaining;

	archive_entry_set_size(entry, tar->entry_bytes_remaining);

