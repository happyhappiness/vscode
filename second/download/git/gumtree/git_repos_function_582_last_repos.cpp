char *get_head_description(void)
{
	struct strbuf desc = STRBUF_INIT;
	struct wt_status_state state;
	memset(&state, 0, sizeof(state));
	wt_status_get_state(&state, 1);
	if (state.rebase_in_progress ||
	    state.rebase_interactive_in_progress)
		strbuf_addf(&desc, _("(no branch, rebasing %s)"),
			    state.branch);
	else if (state.bisect_in_progress)
		strbuf_addf(&desc, _("(no branch, bisect started on %s)"),
			    state.branch);
	else if (state.detached_from) {
		if (state.detached_at)
			/*
			 * TRANSLATORS: make sure this matches "HEAD
			 * detached at " in wt-status.c
			 */
			strbuf_addf(&desc, _("(HEAD detached at %s)"),
				state.detached_from);
		else
			/*
			 * TRANSLATORS: make sure this matches "HEAD
			 * detached from " in wt-status.c
			 */
			strbuf_addf(&desc, _("(HEAD detached from %s)"),
				state.detached_from);
	}
	else
		strbuf_addstr(&desc, _("(no branch)"));
	free(state.branch);
	free(state.onto);
	free(state.detached_from);
	return strbuf_detach(&desc, NULL);
}