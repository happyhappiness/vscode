static void check_timeout(void)
{
	time_t t;

	if (!io_timeout || ignore_timeout)
		return;

	if (!last_io_in) {
		last_io_in = time(NULL);
		return;
	}

	t = time(NULL);

	if (t - last_io_in >= io_timeout) {
		if (!am_server && !am_daemon) {
			rprintf(FERROR, "io timeout after %d seconds -- exiting\n",
				(int)(t-last_io_in));
		}
		exit_cleanup(RERR_TIMEOUT);
	}
}