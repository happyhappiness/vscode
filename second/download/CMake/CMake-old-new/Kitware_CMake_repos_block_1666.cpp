{
			/* All of CFDATA in a folder has been handled. */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT, "Invalid CFDATA");
			return (ARCHIVE_FATAL);
		}