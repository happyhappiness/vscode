void display_throughput(struct progress *progress, off_t total)
{
	struct throughput *tp;
	struct timeval tv;
	unsigned int misecs;

	if (!progress)
		return;
	tp = progress->throughput;

	gettimeofday(&tv, NULL);

	if (!tp) {
		progress->throughput = tp = calloc(1, sizeof(*tp));
		if (tp) {
			tp->prev_total = tp->curr_total = total;
			tp->prev_tv = tv;
		}
		return;
	}
	tp->curr_total = total;

	/*
	 * We have x = bytes and y = microsecs.  We want z = KiB/s:
	 *
	 *	z = (x / 1024) / (y / 1000000)
	 *	z = x / y * 1000000 / 1024
	 *	z = x / (y * 1024 / 1000000)
	 *	z = x / y'
	 *
	 * To simplify things we'll keep track of misecs, or 1024th of a sec
	 * obtained with:
	 *
	 *	y' = y * 1024 / 1000000
	 *	y' = y / (1000000 / 1024)
	 *	y' = y / 977
	 */
	misecs = (tv.tv_sec - tp->prev_tv.tv_sec) * 1024;
	misecs += (int)(tv.tv_usec - tp->prev_tv.tv_usec) / 977;

	if (misecs > 512) {
		struct strbuf buf = STRBUF_INIT;
		unsigned int count, rate;

		count = total - tp->prev_total;
		tp->prev_total = total;
		tp->prev_tv = tv;
		tp->avg_bytes += count;
		tp->avg_misecs += misecs;
		rate = tp->avg_bytes / tp->avg_misecs;
		tp->avg_bytes -= tp->last_bytes[tp->idx];
		tp->avg_misecs -= tp->last_misecs[tp->idx];
		tp->last_bytes[tp->idx] = count;
		tp->last_misecs[tp->idx] = misecs;
		tp->idx = (tp->idx + 1) % TP_IDX_MAX;

		throughput_string(&buf, total, rate);
		strncpy(tp->display, buf.buf, sizeof(tp->display));
		strbuf_release(&buf);
		if (progress->last_value != -1 && progress_update)
			display(progress, progress->last_value, NULL);
	}
}