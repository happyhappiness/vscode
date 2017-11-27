static int do_loop (void)
{
	struct timeval tv_now;
	struct timeval tv_next;
	struct timeval tv_wait;
	struct timespec ts_wait;

	while (loop == 0)
	{
		if (gettimeofday (&tv_next, NULL) < 0)
		{
			char errbuf[1024];
			ERROR ("gettimeofday failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}
		tv_next.tv_sec += interval_g;

#if HAVE_LIBKSTAT
		update_kstat ();
#endif

		/* Issue all plugins */
		plugin_read_all ();

		if (gettimeofday (&tv_now, NULL) < 0)
		{
			char errbuf[1024];
			ERROR ("gettimeofday failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}

		if (timeval_cmp (tv_next, tv_now, &tv_wait) <= 0)
		{
			WARNING ("Not sleeping because the next interval is "
					"%i.%06i seconds in the past!",
					(int) tv_wait.tv_sec, (int) tv_wait.tv_usec);
			continue;
		}

		ts_wait.tv_sec  = tv_wait.tv_sec;
		ts_wait.tv_nsec = (long) (1000 * tv_wait.tv_usec);

		while ((loop == 0) && (nanosleep (&ts_wait, &ts_wait) == -1))
		{
			if (errno != EINTR)
			{
				char errbuf[1024];
				ERROR ("nanosleep failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}
		}
	} /* while (loop == 0) */

	DEBUG ("return (0);");
	return (0);
}