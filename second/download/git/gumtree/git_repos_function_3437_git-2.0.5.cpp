static void handle_builtin(int argc, const char **argv)
{
	const char *cmd = argv[0];
	int i;
	static const char ext[] = STRIP_EXTENSION;

	if (sizeof(ext) > 1) {
		i = strlen(argv[0]) - strlen(ext);
		if (i > 0 && !strcmp(argv[0] + i, ext)) {
			char *argv0 = xstrdup(argv[0]);
			argv[0] = cmd = argv0;
			argv0[i] = '\0';
		}
	}

	/* Turn "git cmd --help" into "git help cmd" */
	if (argc > 1 && !strcmp(argv[1], "--help")) {
		argv[1] = argv[0];
		argv[0] = cmd = "help";
	}

	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		struct cmd_struct *p = commands+i;
		if (strcmp(p->cmd, cmd))
			continue;
		exit(run_builtin(p, argc, argv));
	}
}