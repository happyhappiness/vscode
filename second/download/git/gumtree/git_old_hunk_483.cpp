#else
#define strip_extension(cmd)
#endif

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
	if (builtin)
		exit(run_builtin(builtin, argc, argv));
}

static void execv_dashed_external(const char **argv)
{
	struct strbuf cmd = STRBUF_INIT;
	const char *tmp;
	int status;

	if (use_pager == -1)
		use_pager = check_pager_config(argv[0]);
	commit_pager_choice();

	strbuf_addf(&cmd, "git-%s", argv[0]);

