static int gitdiff_renamedst(struct apply_state *state,
			     const char *line,
			     struct patch *patch)
{
	patch->is_rename = 1;
	free(patch->new_name);
	patch->new_name = find_name(state, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
	return 0;
}