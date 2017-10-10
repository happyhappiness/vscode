	 * diff before committing.
	 */
	if (s->fp != stdout) {
		rev.diffopt.use_color = 0;
		wt_status_add_cut_line(s->fp);
	}
	if (s->verbose > 1 && s->commitable) {
		/* print_updated() printed a header, so do we */
		if (s->fp != stdout)
			wt_status_print_trailer(s);
		status_printf_ln(s, c, _("Changes to be committed:"));
		rev.diffopt.a_prefix = "c/";
		rev.diffopt.b_prefix = "i/";
	} /* else use prefix as per user config */
	run_diff_index(&rev, 1);
	if (s->verbose > 1 &&
	    wt_status_check_worktree_changes(s, &dirty_submodules)) {
		status_printf_ln(s, c,
			"--------------------------------------------------");
		status_printf_ln(s, c, _("Changes not staged for commit:"));
		setup_work_tree();
		rev.diffopt.a_prefix = "i/";
		rev.diffopt.b_prefix = "w/";
		run_diff_files(&rev, 0);
	}
}

static void wt_status_print_tracking(struct wt_status *s)
{
	struct strbuf sb = STRBUF_INIT;
	const char *cp, *ep;
