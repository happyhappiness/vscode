int cmd_cherry_pick(int argc, const char **argv, const char *prefix)
{
	struct replay_opts opts;
	int res;

	memset(&opts, 0, sizeof(opts));
	opts.action = REPLAY_PICK;
	git_config(git_default_config, NULL);
	parse_args(argc, argv, &opts);
	res = sequencer_pick_revisions(&opts);
	if (res < 0)
		die(_("cherry-pick failed"));
	return res;
}