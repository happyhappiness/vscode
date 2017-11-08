static int gitdiff_newmode(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	patch->new_mode = strtoul(line, NULL, 8);
	return 0;
}