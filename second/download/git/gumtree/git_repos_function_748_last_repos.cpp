int parse_config_key(const char *var,
		     const char *section,
		     const char **subsection, int *subsection_len,
		     const char **key)
{
	const char *dot;

	/* Does it start with "section." ? */
	if (!skip_prefix(var, section, &var) || *var != '.')
		return -1;

	/*
	 * Find the key; we don't know yet if we have a subsection, but we must
	 * parse backwards from the end, since the subsection may have dots in
	 * it, too.
	 */
	dot = strrchr(var, '.');
	*key = dot + 1;

	/* Did we have a subsection at all? */
	if (dot == var) {
		if (subsection) {
			*subsection = NULL;
			*subsection_len = 0;
		}
	}
	else {
		if (!subsection)
			return -1;
		*subsection = var + 1;
		*subsection_len = dot - *subsection;
	}

	return 0;
}