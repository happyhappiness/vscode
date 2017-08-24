((timetype & ARCHIVE_MATCH_NEWER) || JUST_EQUAL(timetype)) {
			a->newer_mtime_filter = timetype;
			a->newer_mtime_sec = mtime_sec;
			a->newer_mtime_nsec = mtime_nsec;
			a->setflag |= TIME_IS_SET;
		}