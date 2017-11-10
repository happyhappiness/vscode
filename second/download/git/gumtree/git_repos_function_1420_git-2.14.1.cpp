static void patch_stats(struct apply_state *state, struct patch *patch)
{
	int lines = patch->lines_added + patch->lines_deleted;

	if (lines > state->max_change)
		state->max_change = lines;
	if (patch->old_name) {
		int len = quote_c_style(patch->old_name, NULL, NULL, 0);
		if (!len)
			len = strlen(patch->old_name);
		if (len > state->max_len)
			state->max_len = len;
	}
	if (patch->new_name) {
		int len = quote_c_style(patch->new_name, NULL, NULL, 0);
		if (!len)
			len = strlen(patch->new_name);
		if (len > state->max_len)
			state->max_len = len;
	}
}