int cmd_cherry_pick(int argc, const char **argv, const char *prefix)
{
	struct replay_opts opts = REPLAY_OPTS_INIT;
	int res;

	opts.action = REPLAY_PICK;
	git_config(git_default_config, NULL);
	res = run_sequencer(argc, argv, &opts);
	if (res < 0)
		die(_("cherry-pick failed"));
	return res;
}