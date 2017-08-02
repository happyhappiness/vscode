archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Padding wrong size: %ju should be 1 or 0",
		    (uintmax_t)ar->entry_padding)