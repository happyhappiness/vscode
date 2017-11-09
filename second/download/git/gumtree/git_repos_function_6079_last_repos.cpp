static int run_file_diff(int prompt, const char *prefix,
			 int argc, const char **argv)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	const char *env[] = {
		"GIT_PAGER=", "GIT_EXTERNAL_DIFF=git-difftool--helper", NULL,
		NULL
	};
	int ret = 0, i;

	if (prompt > 0)
		env[2] = "GIT_DIFFTOOL_PROMPT=true";
	else if (!prompt)
		env[2] = "GIT_DIFFTOOL_NO_PROMPT=true";


	argv_array_push(&args, "diff");
	for (i = 0; i < argc; i++)
		argv_array_push(&args, argv[i]);
	ret = run_command_v_opt_cd_env(args.argv, RUN_GIT_CMD, prefix, env);
	exit(ret);
}