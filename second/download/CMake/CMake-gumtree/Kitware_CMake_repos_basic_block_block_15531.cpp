{
		file->flg |= ATIME_IS_SET;
		file->times[ATIME].time = archive_entry_atime(entry);
		file->times[ATIME].time_ns = archive_entry_atime_nsec(entry);
	}