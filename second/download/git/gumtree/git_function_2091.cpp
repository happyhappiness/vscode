static int push_dav(int nr_spec, char **specs)
{
	const char **argv = xmalloc((10 + nr_spec) * sizeof(char*));
	int argc = 0, i;

	argv[argc++] = "http-push";
	argv[argc++] = "--helper-status";
	if (options.dry_run)
		argv[argc++] = "--dry-run";
	if (options.verbosity > 1)
		argv[argc++] = "--verbose";
	argv[argc++] = url.buf;
	for (i = 0; i < nr_spec; i++)
		argv[argc++] = specs[i];
	argv[argc++] = NULL;

	if (run_command_v_opt(argv, RUN_GIT_CMD))
		die("git-%s failed", argv[0]);
	free(argv);
	return 0;
}