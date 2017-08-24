{
		fileTime -= EPOC_TIME;
		/* milli seconds base */
		*timep = (time_t)(fileTime / 10000000);
		/* nano seconds base */
		*ns = (long)(fileTime % 10000000) * 100;
	}