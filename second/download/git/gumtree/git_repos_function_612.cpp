void display_throughput(struct progress *progress, off_t total)
{
	struct throughput *tp;
	uint64_t now_ns;
	unsigned int misecs, count, rate;
	struct strbuf buf = STRBUF_INIT;

	if (!progress)
		return;
	tp = progress->throughput;

	now_ns = getnanotime();

	if (!tp) {
		progress->throughput = tp = calloc(1, sizeof(*tp));
		if (tp) {
			tp->prev_total = tp->curr_total = total;
			tp->prev_ns = now_ns;
		}
		return;
	}
	tp->curr_total = total;

	/* only update throughput every 0.5 s */
	if (now_ns - tp->prev_ns <= 500000000)
		return;

	/*
	 * We have x = bytes and y = nanosecs.  We want z = KiB/s:
	 *
	 *	z = (x / 1024) / (y / 1000000000)
	 *	z = x / y * 1000000000 / 1024
	 *	z = x / (y * 1024 / 1000000000)
	 *	z = x / y'
	 *
	 * To simplify things we'll keep track of misecs, or 1024th of a sec
	 * obtained with:
	 *
	 *	y' = y * 1024 / 1000000000
	 *	y' = y * (2^10 / 2^42) * (2^42 / 1000000000)
	 *	y' = y / 2^32 * 4398
	 *	y' = (y * 4398) >> 32
	 */
	misecs = ((now_ns - tp->prev_ns) * 4398) >> 32;

	count = total - tp->prev_total;
	tp->prev_total = total;
	tp->prev_ns = now_ns;
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