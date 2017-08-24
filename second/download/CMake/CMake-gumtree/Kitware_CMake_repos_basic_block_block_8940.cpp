{
			a->older_mtime_filter = timetype;
			a->older_mtime_sec = mtime_sec;
			a->older_mtime_nsec = mtime_nsec;
			a->setflag |= TIME_IS_SET;
		}