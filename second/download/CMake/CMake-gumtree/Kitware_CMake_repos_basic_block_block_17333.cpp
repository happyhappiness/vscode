(archive_entry_hardlink(file->entry) == NULL) {
		r = save_xattrs(a, file);
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}