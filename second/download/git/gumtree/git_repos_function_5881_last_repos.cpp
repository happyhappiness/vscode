int cmd_revert(int argc, const char **argv, const char *prefix)
{
	struct replay_opts opts = REPLAY_OPTS_INIT;
	int res;

	if (isatty(0))
		opts.edit = 1;
	opts.action = REPLAY_REVERT;
	git_config(git_default_config, NULL);
	res = run_sequencer(argc, argv, &opts);
	if (res < 0)
		die(_("revert failed"));
	return res;
}