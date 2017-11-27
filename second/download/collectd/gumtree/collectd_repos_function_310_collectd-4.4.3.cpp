int timeval_sub_timespec (struct timeval *tv0, struct timeval *tv1, struct timespec *ret)
{
	if ((tv0 == NULL) || (tv1 == NULL) || (ret == NULL))
		return (-2);

	if ((tv0->tv_sec < tv1->tv_sec)
			|| ((tv0->tv_sec == tv1->tv_sec) && (tv0->tv_usec < tv1->tv_usec)))
		return (-1);

	ret->tv_sec  = tv0->tv_sec - tv1->tv_sec;
	ret->tv_nsec = 1000 * ((long) (tv0->tv_usec - tv1->tv_usec));

	if (ret->tv_nsec < 0)
	{
		assert (ret->tv_sec > 0);

		ret->tv_nsec += 1000000000;
		ret->tv_sec  -= 1;
	}

	return (0);
}