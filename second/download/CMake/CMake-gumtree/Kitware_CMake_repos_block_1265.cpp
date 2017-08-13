{
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated ZIP end-of-file record");
			return (ARCHIVE_FATAL);
		}