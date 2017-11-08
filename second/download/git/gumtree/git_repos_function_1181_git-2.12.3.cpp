static int gitdiff_oldmode(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	patch->old_mode = strtoul(line, NULL, 8);
	return 0;
}