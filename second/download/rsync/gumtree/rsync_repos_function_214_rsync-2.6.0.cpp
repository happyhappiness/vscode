void glob_expand(char *base1, char **argv, int *argc, int maxargs)
{
	char *s = argv[*argc];
	char *p, *q;
	char *base = base1;
	int base_len = strlen(base);

	if (!s || !*s) return;

	if (strncmp(s, base, base_len) == 0)
		s += base_len;

	s = strdup(s);
	if (!s) out_of_memory("glob_expand");

	if (asprintf(&base," %s/", base1) <= 0) out_of_memory("glob_expand");
	base_len++;

	q = s;
	while ((p = strstr(q,base)) && ((*argc) < maxargs)) {
		/* split it at this point */
		*p = 0;
		glob_expand_one(q, argv, argc, maxargs);
		q = p + base_len;
	}

	if (*q && (*argc < maxargs)) glob_expand_one(q, argv, argc, maxargs);

	free(s);
	free(base);
}