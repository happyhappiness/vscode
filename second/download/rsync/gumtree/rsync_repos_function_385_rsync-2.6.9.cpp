static void output_summary(void)
{
	if (do_stats) {
		rprintf(FCLIENT, "\n");
		rprintf(FINFO,"Number of files: %d\n", stats.num_files);
		rprintf(FINFO,"Number of files transferred: %d\n",
			stats.num_transferred_files);
		rprintf(FINFO,"Total file size: %s bytes\n",
			human_num(stats.total_size));
		rprintf(FINFO,"Total transferred file size: %s bytes\n",
			human_num(stats.total_transferred_size));
		rprintf(FINFO,"Literal data: %s bytes\n",
			human_num(stats.literal_data));
		rprintf(FINFO,"Matched data: %s bytes\n",
			human_num(stats.matched_data));
		rprintf(FINFO,"File list size: %d\n", stats.flist_size);
		if (stats.flist_buildtime) {
			rprintf(FINFO,
				"File list generation time: %.3f seconds\n",
				(double)stats.flist_buildtime / 1000);
			rprintf(FINFO,
				"File list transfer time: %.3f seconds\n",
				(double)stats.flist_xfertime / 1000);
		}
		rprintf(FINFO,"Total bytes sent: %s\n",
			human_num(total_written));
		rprintf(FINFO,"Total bytes received: %s\n",
			human_num(total_read));
	}

	if (verbose || do_stats) {
		rprintf(FCLIENT, "\n");
		rprintf(FINFO,
			"sent %s bytes  received %s bytes  %s bytes/sec\n",
			human_num(total_written), human_num(total_read),
			human_dnum((total_written + total_read)/(0.5 + (endtime - starttime)), 2));
		rprintf(FINFO, "total size is %s  speedup is %.2f\n",
			human_num(stats.total_size),
			(double)stats.total_size / (total_written+total_read));
	}

	fflush(stdout);
	fflush(stderr);
}