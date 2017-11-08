void stop_progress_msg(struct progress **p_progress, const char *msg)
{
	struct progress *progress = *p_progress;
	if (!progress)
		return;
	*p_progress = NULL;
	if (progress->last_value != -1) {
		/* Force the last update */
		char buf[128], *bufp;
		size_t len = strlen(msg) + 5;
		struct throughput *tp = progress->throughput;

		bufp = (len < sizeof(buf)) ? buf : xmalloc(len + 1);
		if (tp) {
			struct strbuf strbuf = STRBUF_INIT;
			unsigned int rate = !tp->avg_misecs ? 0 :
					tp->avg_bytes / tp->avg_misecs;
			throughput_string(&strbuf, tp->curr_total, rate);
			strncpy(tp->display, strbuf.buf, sizeof(tp->display));
			strbuf_release(&strbuf);
		}
		progress_update = 1;
		sprintf(bufp, ", %s.\n", msg);
		display(progress, progress->last_value, bufp);
		if (buf != bufp)
			free(bufp);
	}
	clear_progress_signal();
	free(progress->throughput);
	free(progress);
}