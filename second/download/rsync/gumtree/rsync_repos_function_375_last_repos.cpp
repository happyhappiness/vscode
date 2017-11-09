void glob_expand_module(char *base1, char *arg, char ***argv_p, int *argc_p, int *maxargs_p)
{
	char *p, *s;
	char *base = base1;
	int base_len = strlen(base);

	if (!arg || !*arg)
		return;

	if (strncmp(arg, base, base_len) == 0)
		arg += base_len;

	if (protect_args) {
		glob_expand(arg, argv_p, argc_p, maxargs_p);
		return;
	}

	if (!(arg = strdup(arg)))
		out_of_memory("glob_expand_module");

	if (asprintf(&base," %s/", base1) < 0)
		out_of_memory("glob_expand_module");
	base_len++;

	for (s = arg; *s; s = p + base_len) {
		if ((p = strstr(s, base)) != NULL)
			*p = '\0'; /* split it at this point */
		glob_expand(s, argv_p, argc_p, maxargs_p);
		if (!p)
			break;
	}

	free(arg);
	free(base);
}