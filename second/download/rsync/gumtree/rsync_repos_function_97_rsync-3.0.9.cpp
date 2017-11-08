static void check_timeout(void)
{
	time_t t, chk;

	if (!io_timeout || ignore_timeout)
		return;

	t = time(NULL);

	if (!last_io_in)
		last_io_in = t;

	chk = MAX(last_io_out, last_io_in);
	if (t - chk >= io_timeout) {
		if (am_server || am_daemon)
			exit_cleanup(RERR_TIMEOUT);
		rprintf(FERROR, "[%s] io timeout after %d seconds -- exiting\n",
			who_am_i(), (int)(t-chk));
		exit_cleanup(RERR_TIMEOUT);
	}
}