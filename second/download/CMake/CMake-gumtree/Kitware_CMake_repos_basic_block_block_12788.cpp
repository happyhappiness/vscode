{
		/* Note: tar_atol returns INT64_MAX on overflow */
		tar->entry_bytes_remaining = 0;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Tar entry size overflow");
		return (ARCHIVE_FATAL);
	}