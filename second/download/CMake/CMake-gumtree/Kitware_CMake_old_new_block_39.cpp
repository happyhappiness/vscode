{
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Invalid extended attribute encountered");
			ret = ARCHIVE_WARN;
		}