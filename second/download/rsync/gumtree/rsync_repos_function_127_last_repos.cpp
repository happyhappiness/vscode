static NORETURN void whine_about_eof(BOOL allow_kluge)
{
	if (kluge_around_eof && allow_kluge) {
		int i;
		if (kluge_around_eof > 0)
			exit_cleanup(0);
		/* If we're still here after 10 seconds, exit with an error. */
		for (i = 10*1000/20; i--; )
			msleep(20);
	}

	rprintf(FERROR, RSYNC_NAME ": connection unexpectedly closed "
		"(%s bytes received so far) [%s]\n",
		big_num(stats.total_read), who_am_i());

	exit_cleanup(RERR_STREAMIO);
}