void glob_expand(char *s, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr)
{
	char **argv = *argv_ptr;
	int argc = *argc_ptr;
	int maxargs = *maxargs_ptr;
#if !defined HAVE_GLOB || !defined HAVE_GLOB_H
	if (argc == maxargs) {
		maxargs += MAX_ARGS;
		if (!(argv = realloc_array(argv, char *, maxargs)))
			out_of_memory("glob_expand");
		*argv_ptr = argv;
		*maxargs_ptr = maxargs;
	}
	if (!*s)
		s = ".";
	s = argv[argc++] = strdup(s);
	filter_server_path(s);
#else
	glob_t globbuf;

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