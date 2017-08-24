(archive_entry_ctime_is_set(a->entry)) {
		ctime_sec = archive_entry_ctime(a->entry);
		ctime_nsec = archive_entry_ctime_nsec(a->entry);
	}