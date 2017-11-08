static void split_merge_strategies(const char *string, struct strategy **list,
				   int *nr, int *alloc)
{
	char *p, *q, *buf;

	if (!string)
		return;

	buf = xstrdup(string);
	q = buf;
	for (;;) {
		p = strchr(q, ' ');
		if (!p) {
			ALLOC_GROW(*list, *nr + 1, *alloc);
			(*list)[(*nr)++].name = xstrdup(q);
			free(buf);
			return;
		} else {
			*p = '\0';
			ALLOC_GROW(*list, *nr + 1, *alloc);
			(*list)[(*nr)++].name = xstrdup(q);
			q = ++p;
		}
	}
}