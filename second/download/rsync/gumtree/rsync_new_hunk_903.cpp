	if (maxargs <= argc)
		return;
	if (!*s)
		s = ".";

	if (sanitize_paths)
		s = sanitize_path(NULL, s, "", 0);
	else
		s = strdup(s);
	if (!s)
		out_of_memory("glob_expand");

	memset(&globbuf, 0, sizeof globbuf);
	if (!filter_server_path(s))
		glob(s, 0, NULL, &globbuf);
	if (MAX((int)globbuf.gl_pathc, 1) > maxargs - argc) {
		maxargs += globbuf.gl_pathc + MAX_ARGS;
		if (!(argv = realloc_array(argv, char *, maxargs)))
			out_of_memory("glob_expand");
		*argv_ptr = argv;
		*maxargs_ptr = maxargs;
	}
	if (globbuf.gl_pathc == 0)
		argv[argc++] = s;
	else {
		int i;
		free(s);
		for (i = 0; i < (int)globbuf.gl_pathc; i++) {
			if (!(argv[argc++] = strdup(globbuf.gl_pathv[i])))
				out_of_memory("glob_expand");
		}
	}
	globfree(&globbuf);
#endif
	*argc_ptr = argc;
}

/* This routine is only used in daemon mode. */
void glob_expand_module(char *base1, char *arg, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr)
{
	char *p, *s;
	char *base = base1;
	int base_len = strlen(base);

	if (!arg || !*arg)
		return;

	if (strncmp(arg, base, base_len) == 0)
		arg += base_len;

	if (!(arg = strdup(arg)))
		out_of_memory("glob_expand_module");

	if (asprintf(&base," %s/", base1) <= 0)
		out_of_memory("glob_expand_module");
	base_len++;

	for (s = arg; *s; s = p + base_len) {
		if ((p = strstr(s, base)) != NULL)
			*p = '\0'; /* split it at this point */
		glob_expand(s, argv_ptr, argc_ptr, maxargs_ptr);
		if (!p)
			break;
	}

	free(arg);
	free(base);
}

/**
 * Convert a string to lower case
 **/
void strlower(char *s)
{
	while (*s) {
		if (isUpper(s))
			*s = toLower(s);
		s++;
	}
}

/* Join strings p1 & p2 into "dest" with a guaranteed '/' between them.  (If
 * p1 ends with a '/', no extra '/' is inserted.)  Returns the length of both
