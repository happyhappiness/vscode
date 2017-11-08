static void show_revert_in_progress(struct wt_status *s,
					struct wt_status_state *state,
					const char *color)
{
	status_printf_ln(s, color, _("You are currently reverting commit %s."),
			 find_unique_abbrev(state->revert_head_sha1, DEFAULT_ABBREV));
	if (s->hints) {
		if (has_unmerged(s))
			status_printf_ln(s, color,
				_("  (fix conflicts and run \"git revert --continue\")"));
		else
			status_printf_ln(s, color,
				_("  (all conflicts fixed: run \"git revert --continue\")"));
		status_printf_ln(s, color,
			_("  (use \"git revert --abort\" to cancel the revert operation)"));
	}
	wt_status_print_trailer(s);
}