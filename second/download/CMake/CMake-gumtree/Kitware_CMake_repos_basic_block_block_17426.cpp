(r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Gname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate gname '%s' to UTF-8",
		    archive_entry_gname(file->entry));
		r2 = ARCHIVE_WARN;
	}