static void print_rebase_state(struct wt_status *s,
				struct wt_status_state *state,
				const char *color)
{
	if (state->branch)
		status_printf_ln(s, color,
				 _("You are currently rebasing branch '%s' on '%s'."),
				 state->branch,
				 state->onto);
	else
		status_printf_ln(s, color,
				 _("You are currently rebasing."));
}