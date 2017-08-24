{
		file->flg |= CTIME_IS_SET;
		file->times[CTIME].time = archive_entry_ctime(entry);
		file->times[CTIME].time_ns = archive_entry_ctime_nsec(entry);
	}