static void report(int f)
{
	time_t t = time(NULL);
	extern int am_server;
	extern int am_sender;
	extern int am_daemon;
	extern int do_stats;

	if (am_daemon) {
		syslog(LOG_INFO,"wrote %.0f bytes  read %.0f bytes  total size %.0f\n",
		       (double)stats.total_written,
		       (double)stats.total_read,
		       (double)stats.total_size);
		if (f == -1 || !am_sender) return;
	}

	if (!verbose) return;

	if (am_server && !am_sender) return;

	if (am_server && am_sender) {
		write_longint(f,stats.total_read);
		write_longint(f,stats.total_written);
		write_longint(f,stats.total_size);
		return;
	}
    
	if (!am_sender) {
		int64 r;
		stats.total_written = read_longint(f);
		r = read_longint(f);
		stats.total_size = read_longint(f);
		stats.total_read = r;
	}

	if (do_stats) {
		printf("\nNumber of files: %d\n", stats.num_files);
		printf("Number of files transferred: %d\n", 
		       stats.num_transferred_files);
		printf("Total file size: %.0f bytes\n", 
		       (double)stats.total_size);
		printf("Total transferred file size: %.0f bytes\n", 
		       (double)stats.total_transferred_size);
		printf("Literal data: %.0f bytes\n", 
		       (double)stats.literal_data);
		printf("Matched data: %.0f bytes\n", 
		       (double)stats.matched_data);
		printf("File list size: %d\n", stats.flist_size);
		printf("Total bytes written: %.0f\n", 
		       (double)stats.total_written);
		printf("Total bytes read: %.0f\n\n", 
		       (double)stats.total_read);
	}
	
	printf("wrote %.0f bytes  read %.0f bytes  %.2f bytes/sec\n",
	       (double)stats.total_written,
	       (double)stats.total_read,
	       (stats.total_written+stats.total_read)/(0.5 + (t-starttime)));
	printf("total size is %.0f  speedup is %.2f\n",
	       (double)stats.total_size,
	       (1.0*stats.total_size)/(stats.total_written+stats.total_read));

	fflush(stdout);
	fflush(stderr);
}