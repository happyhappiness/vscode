int read_args(int f_in, char *mod_name, char *buf, size_t bufsiz, int rl_nulls,
	      char ***argv_p, int *argc_p, char **request_p)
{
	int maxargs = MAX_ARGS;
	int dot_pos = 0;
	int argc = 0;
	char **argv, *p;
	int rl_flags = (rl_nulls ? RL_EOL_NULLS : 0);

#ifdef ICONV_OPTION
	rl_flags |= (protect_args && ic_recv != (iconv_t)-1 ? RL_CONVERT : 0);
#endif

	if (!(argv = new_array(char *, maxargs)))
		out_of_memory("read_args");
	if (mod_name)
		argv[argc++] = "rsyncd";

	while (1) {
		if (read_line(f_in, buf, bufsiz, rl_flags) == 0)
			break;

		if (argc == maxargs) {
			maxargs += MAX_ARGS;
			if (!(argv = realloc_array(argv, char *, maxargs)))
				out_of_memory("read_args");
		}

		if (dot_pos) {
			if (request_p) {
				*request_p = strdup(buf);
				request_p = NULL;
			}
			if (mod_name)
				glob_expand_module(mod_name, buf, &argv, &argc, &maxargs);
			else
				glob_expand(buf, &argv, &argc, &maxargs);
		} else {
			if (!(p = strdup(buf)))
				out_of_memory("read_args");
			argv[argc++] = p;
			if (*p == '.' && p[1] == '\0')
				dot_pos = argc;
		}
	}

	*argc_p = argc;
	*argv_p = argv;

	return dot_pos ? dot_pos : argc;
}