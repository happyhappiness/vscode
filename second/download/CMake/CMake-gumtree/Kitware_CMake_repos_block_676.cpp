{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid value for option ``%s''", key);
			return (ARCHIVE_FATAL);
		}