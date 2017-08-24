(archive_entry_dev(file->entry) != 0) {
		r = xmlwrite_fstring(a, writer, "deviceno",
		    "%d", archive_entry_dev(file->entry));
		if (r < 0)
			return (ARCHIVE_FATAL);
	}