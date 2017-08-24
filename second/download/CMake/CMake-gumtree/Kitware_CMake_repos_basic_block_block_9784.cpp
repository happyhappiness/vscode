{
		te->restore_time.mtime = rt->mtime;
		te->restore_time.mtime_nsec = rt->mtime_nsec;
		te->restore_time.atime = rt->atime;
		te->restore_time.atime_nsec = rt->atime_nsec;
		te->restore_time.filetype = rt->filetype;
		te->restore_time.noatime = rt->noatime;
	}