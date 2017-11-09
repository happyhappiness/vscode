static void show_cherry_pick_in_progress(struct wt_status *s,
					struct wt_status_state *state,
					const char *color)
{
	status_printf_ln(s, color, _("You are currently cherry-picking commit %s."),
			find_unique_abbrev(state->cherry_pick_head_sha1, DEFAULT_ABBREV));
	if (s->hints) {
		if (has_unmerged(s))
			status_printf_ln(s, color,
				_("  (fix conflicts and run \"git cherry-pick --continue\")"));
		else
			status_printf_ln(s, color,
				_("  (all conflicts fixed: run \"git cherry-pick --continue\")"));
		status_printf_ln(s, color,
			_("  (use \"git cherry-pick --abort\" to cancel the cherry-pick operation)"));
	}
	wt_longstatus_print_trailer(s);
}