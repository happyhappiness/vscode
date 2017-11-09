static char *find_name_common(struct apply_state *state,
			      const char *line,
			      const char *def,
			      int p_value,
			      const char *end,
			      int terminate)
{
	int len;
	const char *start = NULL;

	if (p_value == 0)
		start = line;
	while (line != end) {
		char c = *line;

		if (!end && isspace(c)) {
			if (c == '\n')
				break;
			if (name_terminate(c, terminate))
				break;
		}
		line++;
		if (c == '/' && !--p_value)
			start = line;
	}
	if (!start)
		return squash_slash(xstrdup_or_null(def));
	len = line - start;
	if (!len)
		return squash_slash(xstrdup_or_null(def));

	/*
	 * Generally we prefer the shorter name, especially
	 * if the other one is just a variation of that with
	 * something else tacked on to the end (ie "file.orig"
	 * or "file~").
	 */
	if (def) {
		int deflen = strlen(def);
		if (deflen < len && !strncmp(start, def, deflen))
			return squash_slash(xstrdup(def));
	}

	if (state->root.len) {
		char *ret = xstrfmt("%s%.*s", state->root.buf, len, start);
		return squash_slash(ret);
	}

	return squash_slash(xmemdupz(start, len));
}