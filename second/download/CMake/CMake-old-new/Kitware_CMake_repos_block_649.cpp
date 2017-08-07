{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid value(over %d) for "
			    "option ``%s''", high, key);
			return (ARCHIVE_FATAL);
		}