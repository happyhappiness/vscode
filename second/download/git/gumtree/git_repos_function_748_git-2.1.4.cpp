static void show_bisect_in_progress(struct wt_status *s,
				struct wt_status_state *state,
				const char *color)
{
	if (state->branch)
		status_printf_ln(s, color,
				 _("You are currently bisecting, started from branch '%s'."),
				 state->branch);
	else
		status_printf_ln(s, color,
				 _("You are currently bisecting."));
	if (s->hints)
		status_printf_ln(s, color,
			_("  (use \"git bisect reset\" to get back to the original branch)"));
	wt_status_print_trailer(s);
}