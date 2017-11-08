static int display(struct progress *progress, unsigned n, const char *done)
{
	const char *eol, *tp;

	if (progress->delay) {
		if (!progress_update || --progress->delay)
			return 0;
		if (progress->total) {
			unsigned percent = n * 100 / progress->total;
			if (percent > progress->delayed_percent_treshold) {
				/* inhibit this progress report entirely */
				clear_progress_signal();
				progress->delay = -1;
				progress->total = 0;
				return 0;
			}
		}
	}

	progress->last_value = n;
	tp = (progress->throughput) ? progress->throughput->display.buf : "";
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