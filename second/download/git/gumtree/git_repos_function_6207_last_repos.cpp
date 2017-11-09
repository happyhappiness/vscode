static void reset_hard(unsigned const char *sha1, int verbose)
{
	int i = 0;
	const char *args[6];

	args[i++] = "read-tree";
	if (verbose)
		args[i++] = "-v";
	args[i++] = "--reset";
	args[i++] = "-u";
	args[i++] = sha1_to_hex(sha1);
	args[i] = NULL;

	if (run_command_v_opt(args, RUN_GIT_CMD))
		die(_("read-tree failed"));
}