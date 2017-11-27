int timeval_cmp (struct timeval tv0, struct timeval tv1, struct timeval *delta)
{
	struct timeval *larger;
	struct timeval *smaller;

	int status;

	NORMALIZE_TIMEVAL (tv0);
	NORMALIZE_TIMEVAL (tv1);

	if ((tv0.tv_sec == tv1.tv_sec) && (tv0.tv_usec == tv1.tv_usec))
	{
		if (delta != NULL) {
			delta->tv_sec  = 0;
			delta->tv_usec = 0;
		}
		return (0);
	}

	if ((tv0.tv_sec < tv1.tv_sec)
			|| ((tv0.tv_sec == tv1.tv_sec) && (tv0.tv_usec < tv1.tv_usec)))
	{
		larger  = &tv1;
		smaller = &tv0;
		status  = -1;
	}
	else
	{
		larger  = &tv0;
		smaller = &tv1;
		status  = 1;
	}

	if (delta != NULL) {
		delta->tv_sec = larger->tv_sec - smaller->tv_sec;

		if (smaller->tv_usec <= larger->tv_usec)
			delta->tv_usec = larger->tv_usec - smaller->tv_usec;
		else
		{
			--delta->tv_sec;
			delta->tv_usec = 1000000 + larger->tv_usec - smaller->tv_usec;
		}
	}

	assert ((delta == NULL)
			|| ((0 <= delta->tv_usec) && (delta->tv_usec < 1000000)));

	return (status);
}