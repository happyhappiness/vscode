static void wt_longstatus_print_state(struct wt_status *s,
				      struct wt_status_state *state)
{
	const char *state_color = color(WT_STATUS_HEADER, s);
	if (state->merge_in_progress)
		show_merge_in_progress(s, state, state_color);
	else if (state->am_in_progress)
		show_am_in_progress(s, state, state_color);
	else if (state->rebase_in_progress || state->rebase_interactive_in_progress)
		show_rebase_in_progress(s, state, state_color);
	else if (state->cherry_pick_in_progress)
		show_cherry_pick_in_progress(s, state, state_color);
	else if (state->revert_in_progress)
		show_revert_in_progress(s, state, state_color);
	if (state->bisect_in_progress)
		show_bisect_in_progress(s, state, state_color);
}