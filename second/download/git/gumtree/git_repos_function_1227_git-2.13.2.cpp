static char *find_name(struct apply_state *state,
		       const char *line,
		       char *def,
		       int p_value,
		       int terminate)
{
	if (*line == '"') {
		char *name = find_name_gnu(state, line, def, p_value);
		if (name)
			return name;
	}

	return find_name_common(state, line, def, p_value, NULL, terminate);
}