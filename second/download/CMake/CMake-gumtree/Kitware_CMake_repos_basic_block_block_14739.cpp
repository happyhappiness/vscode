{
			fe->birthtime = archive_entry_birthtime(entry);
			fe->birthtime_nanos = archive_entry_birthtime_nsec(
			    entry);
		}