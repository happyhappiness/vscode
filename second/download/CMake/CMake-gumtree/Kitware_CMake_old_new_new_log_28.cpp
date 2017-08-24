archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Symbolic or non-octal mode \"%s\" unsupported", val);