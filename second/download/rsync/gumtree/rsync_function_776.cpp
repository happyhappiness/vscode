void glob_expand(char *base1, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr)
{
	char *s = (*argv_ptr)[*argc_ptr];
	char *p, *q;
	char *base = base1;
	int base_len = strlen(base);

	if (!s || !*s)
		return;

	if (strncmp(s, base, base_len) == 0)
		s += base_len;

	if (!(s = strdup(s)))
		out_of_memory("glob_expand");

	if (asprintf(&base," %s/", base1) <= 0)
		out_of_memory("glob_expand");
	base_len++;

	for (q = s; *q; q = p + base_len) {
		if ((p = strstr(q, base)) != NULL)
			*p = '\0'; /* split it at this point */
		glob_expand_one(q, argv_ptr, argc_ptr, maxargs_ptr);
		if (!p)
			break;
	}

	free(s);
	free(base);
}