(archive_entry_ctime_is_set(file->entry)) {
		r = xmlwrite_time(a, writer, "ctime",
		    archive_entry_ctime(file->entry), 1);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}