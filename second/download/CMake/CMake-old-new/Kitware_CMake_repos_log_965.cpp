archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate symlink '%s' to UTF-8",
			    archive_entry_symlink(file->entry))