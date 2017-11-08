static void rprint_progress(OFF_T ofs, OFF_T size, struct timeval *now,
			    int is_last)
{
	char eol[256];
	const char *units;
	int pct = ofs == size ? 100 : (int) (100.0 * ofs / size);
	unsigned long diff;
	double rate, remain;
	int remain_h, remain_m, remain_s;

	if (is_last) {
		/* Compute stats based on the starting info. */
		if (!ph_start.time.tv_sec
		    || !(diff = msdiff(&ph_start.time, now)))
			diff = 1;
		rate = (double) (ofs - ph_start.ofs) * 1000.0 / diff / 1024.0;
		/* Switch to total time taken for our last update. */
		remain = (double) diff / 1000.0;
	} else {
		/* Compute stats based on recent progress. */
		if (!(diff = msdiff(&ph_list[oldest_hpos].time, now)))
			diff = 1;
		rate = (double) (ofs - ph_list[oldest_hpos].ofs) * 1000.0
		     / diff / 1024.0;
		remain = rate ? (double) (size - ofs) / rate / 1000.0 : 0.0;
	}

	if (rate > 1024*1024) {
		rate /= 1024.0 * 1024.0;
		units = "GB/s";
	} else if (rate > 1024) {
		rate /= 1024.0;
		units = "MB/s";
	} else {
		units = "kB/s";
	}

	remain_s = (int) remain % 60;
	remain_m = (int) (remain / 60.0) % 60;
	remain_h = (int) (remain / 3600.0);

	if (is_last) {
		snprintf(eol, sizeof eol, " (xfer#%d, to-check=%d/%d)\n",
			stats.num_transferred_files,
			stats.num_files - stats.current_file_index - 1,
			stats.num_files);
	} else
		strlcpy(eol, "\r", sizeof eol);
	rprintf(FCLIENT, "%12s %3d%% %7.2f%s %4d:%02d:%02d%s",
		human_num(ofs), pct, rate, units,
		remain_h, remain_m, remain_s, eol);
}