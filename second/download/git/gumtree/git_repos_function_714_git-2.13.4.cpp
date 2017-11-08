void stop_progress_msg(struct progress **p_progress, const char *msg)
{
	struct progress *progress = *p_progress;
	if (!progress)
		return;
	*p_progress = NULL;
	if (progress->last_value != -1) {
		/* Force the last update */
		char *buf;
		struct throughput *tp = progress->throughput;

		if (tp) {
			uint64_t now_ns = getnanotime();
			unsigned int misecs, rate;
			misecs = ((now_ns - progress->start_ns) * 4398) >> 32;
			rate = tp->curr_total / (misecs ? misecs : 1);
			throughput_string(&tp->display, tp->curr_total, rate);
		}
		progress_update = 1;
		buf = xstrfmt(", %s.\n", msg);
		display(progress, progress->last_value, buf);
		free(buf);
	}
	clear_progress_signal();
	if (progress->throughput)
		strbuf_release(&progress->throughput->display);
	free(progress->throughput);
	free(progress);
}