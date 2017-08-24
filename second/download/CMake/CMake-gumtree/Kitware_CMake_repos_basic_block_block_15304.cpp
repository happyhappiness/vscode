{
		utc.QuadPart -= EPOC_TIME;
		/* milli seconds base */
		*t = (time_t)(utc.QuadPart / 10000000);
		/* nano seconds base */
		*ns = (long)(utc.QuadPart % 10000000) * 100;
	}