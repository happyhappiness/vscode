
static int do_generic_cmd(const char *me, char *arg)
{
	const char *my_argv[4];

	setup_path();
	if (!arg || !(arg = sq_dequote(arg)) || *arg == '-')
		die("bad argument");
	if (!starts_with(me, "git-"))
		die("bad command");

	my_argv[0] = me + 4;
	my_argv[1] = arg;
	my_argv[2] = NULL;

	return execv_git_cmd(my_argv);
}

static int is_valid_cmd_name(const char *cmd)
{
	/* Test command contains no . or / characters */
	return cmd[strcspn(cmd, "./")] == '\0';
}

