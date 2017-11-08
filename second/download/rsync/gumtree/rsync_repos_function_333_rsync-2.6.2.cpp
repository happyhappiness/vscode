static void report(int f)
{
	time_t t = time(NULL);

	if (do_stats && verbose > 1) {
		/* These come out from every process */
		show_malloc_stats();
		show_flist_stats();
	}

	if (am_generator)
		return;

	if (am_daemon) {
		log_exit(0, __FILE__, __LINE__);
		if (f == -1 || !am_sender) return;
	}

	if (am_server) {
		if (am_sender) {
			int64 w;
			/* store total_written in a temporary
			 * because write_longint changes it */
			w = stats.total_written;
			write_longint(f,stats.total_read);
			write_longint(f,w);
			write_longint(f,stats.total_size);
		}
		return;
	}

	/* this is the client */

	if (!am_sender) {
		int64 r;
		stats.total_written = read_longint(f);
		/* store total_read in a temporary, read_longint changes it */
		r = read_longint(f);
		stats.total_size = read_longint(f);
		stats.total_read = r;
	}

	if (do_stats) {
		rprintf(FINFO,"\nNumber of files: %d\n", stats.num_files);
		rprintf(FINFO,"Number of files transferred: %d\n",
			stats.num_transferred_files);
		rprintf(FINFO,"Total file size: %.0f bytes\n",
			(double)stats.total_size);
		rprintf(FINFO,"Total transferred file size: %.0f bytes\n",
			(double)stats.total_transferred_size);
		rprintf(FINFO,"Literal data: %.0f bytes\n",
			(double)stats.literal_data);
		rprintf(FINFO,"Matched data: %.0f bytes\n",
			(double)stats.matched_data);
		rprintf(FINFO,"File list size: %d\n", stats.flist_size);
		rprintf(FINFO,"Total bytes written: %.0f\n",
			(double)stats.total_written);
		rprintf(FINFO,"Total bytes read: %.0f\n",
			(double)stats.total_read);
	}

	if (verbose || do_stats) {
		rprintf(FINFO,"\nwrote %.0f bytes  read %.0f bytes  %.2f bytes/sec\n",
			(double)stats.total_written,
			(double)stats.total_read,
			(stats.total_written+stats.total_read)/(0.5 + (t-starttime)));
		rprintf(FINFO,"total size is %.0f  speedup is %.2f\n",
			(double)stats.total_size,
			(1.0*stats.total_size)/(stats.total_written+stats.total_read));
	}

	fflush(stdout);
	fflush(stderr);
}