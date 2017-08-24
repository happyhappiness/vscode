(error != NULL) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "%s", error);
			return ARCHIVE_WARN;
		}