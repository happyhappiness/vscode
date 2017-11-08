static void rprint_progress(OFF_T ofs, OFF_T size, struct timeval *now,
			    int is_last)
{
	int pct = (ofs == size) ? 100 : (int)((100.0*ofs)/size);
	unsigned long diff = msdiff(&start_time, now);
	double rate = diff ? (double) (ofs-start_ofs) * 1000.0 / diff / 1024.0 : 0;
	const char *units;
	/* If we've finished transferring this file, show the time taken;
	 * otherwise show expected time to complete.  That's kind of
	 * inconsistent, but people can probably cope.  Hopefully we'll
	 * get more consistent and complete progress reporting soon. --
	 * mbp */
	double remain = is_last ? (double) diff / 1000.0
	              : rate ? (double) (size-ofs) / rate / 1000.0 : 0.0;
	int remain_h, remain_m, remain_s;

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

	rprintf(FINFO, "%12.0f %3d%% %7.2f%s %4d:%02d:%02d%s",
		(double) ofs, pct, rate, units,
		remain_h, remain_m, remain_s,
		is_last ? "\n" : "\r");
}