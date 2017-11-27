static int ping_timeval_add (struct timeval *tv1, struct timeval *tv2,
		struct timeval *res)
{
	res->tv_sec  = tv1->tv_sec  + tv2->tv_sec;
	res->tv_usec = tv1->tv_usec + tv2->tv_usec;

	while (res->tv_usec > 1000000)
	{
		res->tv_usec -= 1000000;
		res->tv_sec++;
	}

	return (0);
}