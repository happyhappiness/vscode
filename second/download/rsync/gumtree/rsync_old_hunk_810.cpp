			if (!(argv = realloc_array(argv, char *, maxargs)))
				out_of_memory("rsync_module");
		}
		if (!(argv[argc] = strdup(p)))
			out_of_memory("rsync_module");

		if (start_glob) {
			if (start_glob == 1) {
				request = strdup(p);
				start_glob++;
			}
			glob_expand(name, &argv, &argc, &maxargs);
		} else
			argc++;

		if (strcmp(line, ".") == 0)
			start_glob = 1;
	}

	verbose = 0; /* future verbosity is controlled by client options */
	argp = argv;
	ret = parse_arguments(&argc, (const char ***) &argp, 0);

	if (filesfrom_fd == 0)
		filesfrom_fd = f_in;

	if (request) {
		if (*auth_user) {
