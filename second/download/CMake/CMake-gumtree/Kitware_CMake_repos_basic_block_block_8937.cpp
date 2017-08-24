{
			a->older_ctime_filter = timetype;
			a->older_ctime_sec = ctime_sec;
			a->older_ctime_nsec = ctime_nsec;
			a->setflag |= TIME_IS_SET;
		}