	 * diff before committing.
	 */
	if (s->fp != stdout) {
		rev.diffopt.use_color = 0;
		wt_status_add_cut_line(s->fp);
	}
	run_diff_index(&rev, 1);
}

static void wt_status_print_tracking(struct wt_status *s)
{
	struct strbuf sb = STRBUF_INIT;
	const char *cp, *ep;
