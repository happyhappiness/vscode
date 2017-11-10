static const char *skip_tree_prefix(struct apply_state *state,
				    const char *line,
				    int llen)
{
	int nslash;
	int i;

	if (!state->p_value)
		return (llen && line[0] == '/') ? NULL : line;

	nslash = state->p_value;
	for (i = 0; i < llen; i++) {
		int ch = line[i];
		if (ch == '/' && --nslash <= 0)
			return (i == 0) ? NULL : &line[i + 1];
	}
	return NULL;
}