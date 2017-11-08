static void show_am_in_progress(struct wt_status *s,
				struct wt_status_state *state,
				const char *color)
{
	status_printf_ln(s, color,
		_("You are in the middle of an am session."));
	if (state->am_empty_patch)
		status_printf_ln(s, color,
			_("The current patch is empty."));
	if (s->hints) {
		if (!state->am_empty_patch)
			status_printf_ln(s, color,
				_("  (fix conflicts and then run \"git am --continue\")"));
		status_printf_ln(s, color,
			_("  (use \"git am --skip\" to skip this patch)"));
		status_printf_ln(s, color,
			_("  (use \"git am --abort\" to restore the original branch)"));
	}
	wt_longstatus_print_trailer(s);
}