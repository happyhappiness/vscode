void glob_expand(char *base, char **argv, int *argc, int maxargs)
{
	char *s = argv[*argc];
	char *p, *q;

	if (!s || !*s) return;

	if (strncmp(s, base, strlen(base)) == 0) {
		s += strlen(base);
	}

	s = strdup(s);
	if (!s) out_of_memory("glob_expand");

	q = s;
	while ((p = strstr(q,base)) && ((*argc) < maxargs)) {
		if (p != q && *(p-1) == ' ' && p[strlen(base)] == '/') {
			/* split it at this point */
			*(p-1) = 0;
			glob_expand_one(q, argv, argc, maxargs);
			q = p+strlen(base)+1;
		} else {
			q++;
		}
	}

	if (*q && (*argc < maxargs)) glob_expand_one(q, argv, argc, maxargs);

	free(s);
}