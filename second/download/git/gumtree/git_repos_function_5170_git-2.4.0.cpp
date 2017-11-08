static int fetch_remote(const char *name)
{
	const char *argv[] = { "fetch", name, NULL, NULL };
	if (verbose) {
		argv[1] = "-v";
		argv[2] = name;
	}
	printf_ln(_("Updating %s"), name);
	if (run_command_v_opt(argv, RUN_GIT_CMD))
		return error(_("Could not fetch %s"), name);
	return 0;
}