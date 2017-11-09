static int tail_match(const char **pattern, const char *path)
{
	const char *p;
	char *pathbuf;

	if (!pattern)
		return 1; /* no restriction */

	pathbuf = xstrfmt("/%s", path);
	while ((p = *(pattern++)) != NULL) {
		if (!wildmatch(p, pathbuf, 0)) {
			free(pathbuf);
			return 1;
		}
	}
	free(pathbuf);
	return 0;
}