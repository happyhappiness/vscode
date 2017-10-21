			*s++ = '/';
		}
	}
	return 0;
}

static void glob_expand_one(char *s, char ***argv_ptr, int *argc_ptr,
			    int *maxargs_ptr)
{
	char **argv = *argv_ptr;
	int argc = *argc_ptr;
	int maxargs = *maxargs_ptr;
#if !(defined(HAVE_GLOB) && defined(HAVE_GLOB_H))
	if (argc == maxargs) {
		maxargs += MAX_ARGS;
		if (!(argv = realloc_array(argv, char *, maxargs)))
			out_of_memory("glob_expand_one");
		*argv_ptr = argv;
		*maxargs_ptr = maxargs;
	}
	if (!*s)
		s = ".";
	s = argv[argc++] = strdup(s);
	exclude_server_path(s);
#else
	glob_t globbuf;
	int i;

	if (maxargs <= argc)
		return;
	if (!*s)
		s = ".";

	if (sanitize_paths)
		s = sanitize_path(NULL, s, "", 0);
	else
		s = strdup(s);

	memset(&globbuf, 0, sizeof globbuf);
	if (!exclude_server_path(s))
		glob(s, 0, NULL, &globbuf);
	if (MAX((int)globbuf.gl_pathc, 1) > maxargs - argc) {
		maxargs += globbuf.gl_pathc + MAX_ARGS;
		if (!(argv = realloc_array(argv, char *, maxargs)))
			out_of_memory("glob_expand_one");
		*argv_ptr = argv;
		*maxargs_ptr = maxargs;
	}
	if (globbuf.gl_pathc == 0)
		argv[argc++] = s;
	else {
		int j = globbuf.gl_pathc;
		free(s);
		for (i = 0; i < j; i++) {
			if (!(argv[argc++] = strdup(globbuf.gl_pathv[i])))
				out_of_memory("glob_expand_one");
		}
	}
	globfree(&globbuf);
#endif
	*argc_ptr = argc;
}

/* This routine is only used in daemon mode. */
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

/**
 * Convert a string to lower case
 **/
void strlower(char *s)
{
	while (*s) {
		if (isupper(*(unsigned char *)s))
			*s = tolower(*(unsigned char *)s);
		s++;
	}
}

/* Join strings p1 & p2 into "dest" with a guaranteed '/' between them.  (If
 * p1 ends with a '/', no extra '/' is inserted.)  Returns the length of both
