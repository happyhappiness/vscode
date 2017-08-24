{
		file->flg |= MTIME_IS_SET;
		file->times[MTIME].time = archive_entry_mtime(entry);
		file->times[MTIME].time_ns = archive_entry_mtime_nsec(entry);
	}