archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to UTF-8",
		    archive_entry_pathname(file->entry))