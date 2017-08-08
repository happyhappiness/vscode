{
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unknown format `%s'", val);
			return ARCHIVE_WARN;
		}