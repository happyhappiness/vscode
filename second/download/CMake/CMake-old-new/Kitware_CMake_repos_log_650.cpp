archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid value(under %d) for "
			    "option ``%s''", low, key);