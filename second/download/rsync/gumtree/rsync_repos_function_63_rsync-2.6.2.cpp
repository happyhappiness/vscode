static void check_timeout(void)
{
	time_t t;

	if (!io_timeout)
		return;

	if (!last_io) {
		last_io = time(NULL);
		return;
	}

	t = time(NULL);

	if (last_io && io_timeout && (t-last_io) >= io_timeout) {
		if (!am_server && !am_daemon) {
			rprintf(FERROR,"io timeout after %d seconds - exiting\n", 
				(int)(t-last_io));
		}
		exit_cleanup(RERR_TIMEOUT);
	}
}