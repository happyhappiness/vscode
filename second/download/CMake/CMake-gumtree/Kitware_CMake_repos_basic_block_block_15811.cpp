(seg > 0xffff) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "Invalid value(over 0xffff) for "
					    "option ``%s''", key);
					return (ARCHIVE_FATAL);
				}