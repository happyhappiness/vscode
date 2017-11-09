int run_add_interactive(const char *revision, const char *patch_mode,
			const struct pathspec *pathspec)
{
	int status, i;
	struct argv_array argv = ARGV_ARRAY_INIT;

	argv_array_push(&argv, "add--interactive");
	if (patch_mode)
		argv_array_push(&argv, patch_mode);
	if (revision)
		argv_array_push(&argv, revision);
	argv_array_push(&argv, "--");
	for (i = 0; i < pathspec->nr; i++)
		/* pass original pathspec, to be re-parsed */
		argv_array_push(&argv, pathspec->items[i].original);

	status = run_command_v_opt(argv.argv, RUN_GIT_CMD);
	argv_array_clear(&argv);
	return status;
}