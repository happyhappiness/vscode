(archive_entry_ctime_is_set(entry))
			sec = archive_entry_ctime(entry);
		else
			sec = archive_entry_mtime(entry)