static int show_recursive(const char *base, int baselen, const char *pathname)
{
	const char **s;

	if (ls_options & LS_RECURSIVE)
		return 1;

	s = pathspec._raw;
	if (!s)
		return 0;

	for (;;) {
		const char *spec = *s++;
		int len, speclen;

		if (!spec)
			return 0;
		if (strncmp(base, spec, baselen))
			continue;
		len = strlen(pathname);
		spec += baselen;
		speclen = strlen(spec);
		if (speclen <= len)
			continue;
		if (spec[len] && spec[len] != '/')
			continue;
		if (memcmp(pathname, spec, len))
			continue;
		return 1;
	}
}