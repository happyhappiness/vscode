static int gitdiff_newmode(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	return parse_mode_line(line, state->linenr, &patch->new_mode);
}