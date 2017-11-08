static void handle_builtin(int argc, const char **argv)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	const char *cmd;
	struct cmd_struct *builtin;

	strip_extension(argv);
	cmd = argv[0];

	/* Turn "git cmd --help" into "git help --exclude-guides cmd" */
	if (argc > 1 && !strcmp(argv[1], "--help")) {
		int i;

		argv[1] = argv[0];
		argv[0] = cmd = "help";

		for (i = 0; i < argc; i++) {
			argv_array_push(&args, argv[i]);
			if (!i)
				argv_array_push(&args, "--exclude-guides");
		}

		argc++;
		argv = args.argv;
	}

	builtin = get_builtin(cmd);
	if (builtin)
		exit(run_builtin(builtin, argc, argv));
	argv_array_clear(&args);
}