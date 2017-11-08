static void output_summary(void)
{
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
		if (stats.flist_buildtime) {
			rprintf(FINFO,
				"File list generation time: %.3f seconds\n",
				(double)stats.flist_buildtime / 1000);
			rprintf(FINFO,
				"File list transfer time: %.3f seconds\n",
				(double)stats.flist_xfertime / 1000);
		}
		rprintf(FINFO,"Total bytes sent: %.0f\n",
			(double)total_written);
		rprintf(FINFO,"Total bytes received: %.0f\n",
			(double)total_read);
	}

	if (verbose || do_stats) {
		rprintf(FINFO,
			"\nsent %.0f bytes  received %.0f bytes  %.2f bytes/sec\n",
			(double)total_written, (double)total_read,
			(total_written + total_read)/(0.5 + (endtime - starttime)));
		rprintf(FINFO, "total size is %.0f  speedup is %.2f\n",
			(double)stats.total_size,
			(double)stats.total_size / (total_written+total_read));
	}

	fflush(stdout);
	fflush(stderr);
}