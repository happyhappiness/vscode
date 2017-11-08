static void handle_builtin(int argc, const char **argv)
{
	const char *cmd;
	struct cmd_struct *builtin;

	strip_extension(argv);
	cmd = argv[0];

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