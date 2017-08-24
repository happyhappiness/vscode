(archive_entry_atime_is_set(file->entry)) {
		r = xmlwrite_time(a, writer, "atime",
		    archive_entry_atime(file->entry), 1);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}