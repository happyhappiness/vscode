{
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated CAB file data");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}