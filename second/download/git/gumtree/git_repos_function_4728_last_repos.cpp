static void run_shell(void)
{
	int done = 0;
	static const char *help_argv[] = { HELP_COMMAND, NULL };

	if (!access(NOLOGIN_COMMAND, F_OK)) {
		/* Interactive login disabled. */
		const char *argv[] = { NOLOGIN_COMMAND, NULL };
		int status;

		status = run_command_v_opt(argv, 0);
		if (status < 0)
			exit(127);
		exit(status);
	}

	/* Print help if enabled */
	run_command_v_opt(help_argv, RUN_SILENT_EXEC_FAILURE);

	do {
		struct strbuf line = STRBUF_INIT;
		const char *prog;
		char *full_cmd;
		char *rawargs;
		char *split_args;
		const char **argv;
		int code;
		int count;

		fprintf(stderr, "git> ");
		if (strbuf_getline_lf(&line, stdin) == EOF) {
			fprintf(stderr, "\n");
			strbuf_release(&line);
			break;
		}
		strbuf_trim(&line);
		rawargs = strbuf_detach(&line, NULL);
		split_args = xstrdup(rawargs);
		count = split_cmdline(split_args, &argv);
		if (count < 0) {
			fprintf(stderr, "invalid command format '%s': %s\n", rawargs,
				split_cmdline_strerror(count));
			free(split_args);
			free(rawargs);
			continue;
		}

		prog = argv[0];
		if (!strcmp(prog, "")) {
		} else if (!strcmp(prog, "quit") || !strcmp(prog, "logout") ||
			   !strcmp(prog, "exit") || !strcmp(prog, "bye")) {
			done = 1;
		} else if (is_valid_cmd_name(prog)) {
			full_cmd = make_cmd(prog);
			argv[0] = full_cmd;
			code = run_command_v_opt(argv, RUN_SILENT_EXEC_FAILURE);
			if (code == -1 && errno == ENOENT) {
				fprintf(stderr, "unrecognized command '%s'\n", prog);
			}
			free(full_cmd);
		} else {
			fprintf(stderr, "invalid command format '%s'\n", prog);
		}

		free(argv);
		free(rawargs);
	} while (!done);
}