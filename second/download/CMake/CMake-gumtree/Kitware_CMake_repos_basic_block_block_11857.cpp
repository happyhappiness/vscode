{
		tm.tm_hour -= offset / 4;
		tm.tm_min -= (offset % 4) * 15;
	}