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