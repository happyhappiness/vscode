static void rprint_progress(OFF_T ofs, OFF_T size, struct timeval *now,
			    int is_last)
{
	char rembuf[64], eol[128];
	const char *units;
	unsigned long diff;
	double rate, remain;
	int pct;

	if (is_last) {
		int len = snprintf(eol, sizeof eol,
			" (xfr#%d, %s-chk=%d/%d)\n",
			stats.xferred_files, flist_eof ? "to" : "ir",
			stats.num_files - current_file_index - 1,
			stats.num_files);
		if (INFO_GTE(PROGRESS, 2)) {
			static int last_len = 0;
			/* Drop \n and pad with spaces if line got shorter. */
			if (last_len < --len)
				last_len = len;
			eol[last_len] = '\0';
			while (last_len > len)
				eol[--last_len] = ' ';
			is_last = 0;
		}
		/* Compute stats based on the starting info. */
		if (!ph_start.time.tv_sec
		    || !(diff = msdiff(&ph_start.time, now)))
			diff = 1;
		rate = (double) (ofs - ph_start.ofs) * 1000.0 / diff / 1024.0;
		/* Switch to total time taken for our last update. */
		remain = (double) diff / 1000.0;
	} else {
		strlcpy(eol, "  ", sizeof eol);
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

	if (remain < 0)
		strlcpy(rembuf, "  ??:??:??", sizeof rembuf);
	else {
		snprintf(rembuf, sizeof rembuf, "%4d:%02d:%02d",
			 (int) (remain / 3600.0),
			 (int) (remain / 60.0) % 60,
			 (int) remain % 60);
	}

	output_needs_newline = 0;
	pct = ofs == size ? 100 : (int) (100.0 * ofs / size);
	rprintf(FCLIENT, "\r%15s %3d%% %7.2f%s %s%s",
		human_num(ofs), pct, rate, units, rembuf, eol);
	if (!is_last) {
		output_needs_newline = 1;
		rflush(FCLIENT);
	}
}