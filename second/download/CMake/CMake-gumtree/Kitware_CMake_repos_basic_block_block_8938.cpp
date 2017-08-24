{
			a->newer_ctime_filter = timetype;
			a->newer_ctime_sec = ctime_sec;
			a->newer_ctime_nsec = ctime_nsec;
			a->setflag |= TIME_IS_SET;
		}