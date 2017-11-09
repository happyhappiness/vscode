static int gitdiff_similarity(struct apply_state *state,
			      const char *line,
			      struct patch *patch)
{
	unsigned long val = strtoul(line, NULL, 10);
	if (val <= 100)
		patch->score = val;
	return 0;
}