static int gitdiff_oldmode(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	return parse_mode_line(line, state->linenr, &patch->old_mode);
}