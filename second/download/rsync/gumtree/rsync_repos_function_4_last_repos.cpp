int msleep(int t)
{
#ifdef HAVE_USLEEP
	usleep(t*1000);
#else
	int tdiff = 0;
	struct timeval tval, t1, t2;

	gettimeofday(&t1, NULL);

	while (tdiff < t) {
		tval.tv_sec = (t-tdiff)/1000;
		tval.tv_usec = 1000*((t-tdiff)%1000);

		errno = 0;
		select(0,NULL,NULL, NULL, &tval);

		gettimeofday(&t2, NULL);
		tdiff = (t2.tv_sec - t1.tv_sec)*1000 +
			(t2.tv_usec - t1.tv_usec)/1000;
		if (tdiff < 0)
			t1 = t2; /* Time went backwards, so start over. */
	}
#endif

	return True;
}