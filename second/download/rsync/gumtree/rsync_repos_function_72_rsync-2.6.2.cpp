static void whine_about_eof(void)
{
	if (kludge_around_eof)
		exit_cleanup(0);
	else {
		rprintf(FERROR,
			"%s: connection unexpectedly closed "
			"(%.0f bytes read so far)\n",
			RSYNC_NAME, (double)stats.total_read);

		exit_cleanup(RERR_STREAMIO);
	}
}