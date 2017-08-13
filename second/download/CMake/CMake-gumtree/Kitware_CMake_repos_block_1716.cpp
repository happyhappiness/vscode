{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Truncated ar archive");
			return (ARCHIVE_FATAL);
		}