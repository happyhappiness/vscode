	tp = (progress->throughput) ? progress->throughput->display : "";
	eol = done ? done : "   \r";
	if (progress->total) {
		unsigned percent = n * 100 / progress->total;
		if (percent != progress->last_percent || progress_update) {
			progress->last_percent = percent;
			if (is_foreground_fd(fileno(stderr)) || done) {
				fprintf(stderr, "%s: %3u%% (%u/%u)%s%s",
					progress->title, percent, n,
					progress->total, tp, eol);
				fflush(stderr);
			}
			progress_update = 0;
			return 1;
		}
	} else if (progress_update) {
		if (is_foreground_fd(fileno(stderr)) || done) {
			fprintf(stderr, "%s: %u%s%s",
				progress->title, n, tp, eol);
			fflush(stderr);
		}
		progress_update = 0;
		return 1;
	}

	return 0;
}
