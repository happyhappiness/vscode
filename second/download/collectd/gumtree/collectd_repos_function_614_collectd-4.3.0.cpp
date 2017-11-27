static int multimeter_timeval_sub (struct timeval *tv1, struct timeval *tv2,
                struct timeval *res)
{
        if ((tv1->tv_sec < tv2->tv_sec) ||
	    ((tv1->tv_sec == tv2->tv_sec) && (tv1->tv_usec < tv2->tv_usec)))
    	        return (-1);

        res->tv_sec  = tv1->tv_sec  - tv2->tv_sec;
        res->tv_usec = tv1->tv_usec - tv2->tv_usec;

        assert ((res->tv_sec > 0) || ((res->tv_sec == 0) && (res->tv_usec > 0)));

        while (res->tv_usec < 0)
        {
	        res->tv_usec += 1000000;
                res->tv_sec--;
        }
	return (0);
}