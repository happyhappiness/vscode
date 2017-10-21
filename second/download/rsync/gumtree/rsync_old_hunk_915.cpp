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
