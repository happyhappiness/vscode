archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Unrecognized file type \"%s\"; assuming \"file\"", val)