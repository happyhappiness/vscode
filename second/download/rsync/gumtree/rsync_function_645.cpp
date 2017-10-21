void glob_expand(char *base1, char **argv, int *argc, int maxargs)
{
	char *s = argv[*argc];
	char *p, *q;
	char *base = base1;

	if (!s || !*s) return;

	if (strncmp(s, base, strlen(base)) == 0) {
		s += strlen(base);
	}

	s = strdup(s);
	if (!s) out_of_memory("glob_expand");

	base = (char *)malloc(strlen(base1)+3);
	if (!base) out_of_memory("glob_expand");

	sprintf(base," %s/", base1);

	q = s;
	while ((p = strstr(q,base)) && ((*argc) < maxargs)) {
		/* split it at this point */
		*p = 0;
		glob_expand_one(q, argv, argc, maxargs);
		q = p+strlen(base);
	}

	if (*q && (*argc < maxargs)) glob_expand_one(q, argv, argc, maxargs);

	free(s);
	free(base);
}