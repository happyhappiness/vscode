static void whine_about_eof(int fd)
{
	if (kluge_around_eof && fd == sock_f_in) {
		int i;
		if (kluge_around_eof > 0)
			exit_cleanup(0);
		/* If we're still here after 10 seconds, exit with an error. */
		for (i = 10*1000/20; i--; )
			msleep(20);
	}

	rprintf(FERROR, RSYNC_NAME ": connection unexpectedly closed "
		"(%.0f bytes received so far) [%s]\n",
		(double)stats.total_read, who_am_i());

	exit_cleanup(RERR_STREAMIO);
}