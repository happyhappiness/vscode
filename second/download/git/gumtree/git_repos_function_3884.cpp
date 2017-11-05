static void handle_builtin(int argc, const char **argv)
{
	const char *cmd = argv[0];
	int i;
	static const char ext[] = STRIP_EXTENSION;
	struct cmd_struct *builtin;

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

	builtin = get_builtin(cmd);
	if (builtin) {
		if (saved_environment && (builtin->option & NO_SETUP))
			restore_env();
		else
			exit(run_builtin(builtin, argc, argv));
	}
}