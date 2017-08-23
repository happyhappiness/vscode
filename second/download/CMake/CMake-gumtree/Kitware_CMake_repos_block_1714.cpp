{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Truncated input file");
			return (ARCHIVE_FATAL);
		}