static void die_from_readerr (int err)
{
	/* this prevents us trying to write errors on a dead socket */
	io_multiplexing_close();
				
	rprintf(FERROR, "%s: read error: %s\n",
		RSYNC_NAME, strerror (err));
	exit_cleanup(RERR_STREAMIO);
}