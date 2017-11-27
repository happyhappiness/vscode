static int timeval_sub (const struct timeval *tv0, const struct timeval *tv1)
{
	int sec;
	int usec;

	if ((tv0->tv_sec < tv1->tv_sec)
			|| ((tv0->tv_sec == tv1->tv_sec) && (tv0->tv_usec < tv1->tv_usec)))
		return (0);

	sec  = tv0->tv_sec  - tv1->tv_sec;
	usec = tv0->tv_usec - tv1->tv_usec;

	while (usec < 0)
	{
		usec += 1000000;
		sec  -= 1;
	}

	if (sec < 0)
		return (0);

	return ((sec * 1000) + ((usec + 500) / 1000));
}