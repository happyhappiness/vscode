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
