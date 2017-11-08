int cmd_revert(int argc, const char **argv, const char *prefix)
{
	struct replay_opts opts;
	int res;

	memset(&opts, 0, sizeof(opts));
	if (isatty(0))
		opts.edit = 1;
	opts.action = REPLAY_REVERT;
	git_config(git_default_config, NULL);
	parse_args(argc, argv, &opts);
	res = sequencer_pick_revisions(&opts);
	if (res < 0)
		die(_("revert failed"));
	return res;
}