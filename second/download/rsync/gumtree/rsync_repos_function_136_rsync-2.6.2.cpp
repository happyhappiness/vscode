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
		diff = msdiff(&ph_start.time, now);
		if (!diff)
			diff = 1;
		rate = (double) (ofs - ph_start.ofs) * 1000.0 / diff / 1024.0;
		/* Switch to total time taken for our last update. */
		remain = (double) diff / 1000.0;
	} else {
		/* Compute stats based on recent progress. */
		diff = msdiff(&ph_list[oldest_hpos].time, now);
		rate = diff ? (double) (ofs - ph_list[oldest_hpos].ofs) * 1000.0
		    / diff / 1024.0 : 0;
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
		snprintf(eol, sizeof eol, "  (%d, %.1f%% of %d)\n",
			stats.num_transferred_files,
			(float)((stats.current_file_index+1) * 100)
				/ stats.num_files,
			stats.num_files);
	} else
		strcpy(eol, "\r");
	rprintf(FINFO, "%12.0f %3d%% %7.2f%s %4d:%02d:%02d%s",
		(double) ofs, pct, rate, units,
		remain_h, remain_m, remain_s, eol);
}