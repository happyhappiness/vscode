{
			fe->mtime = archive_entry_mtime(entry);
			fe->mtime_nanos = archive_entry_mtime_nsec(entry);
		}