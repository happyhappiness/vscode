(st->st_mtimespec.tv_nsec < archive_entry_mtime_nsec(entry))
		return (1);