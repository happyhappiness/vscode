static int tail_match(const char **pattern, const char *path)
{
	const char *p;
	char pathbuf[PATH_MAX];

	if (!pattern)
		return 1; /* no restriction */

	if (snprintf(pathbuf, sizeof(pathbuf), "/%s", path) > sizeof(pathbuf))
		return error("insanely long ref %.*s...", 20, path);
	while ((p = *(pattern++)) != NULL) {
		if (!wildmatch(p, pathbuf, 0, NULL))
			return 1;
	}
	return 0;
}