		s_r_opt.assume_dashdash = 1;
		argc = setup_revisions(argc, argv, opts->revs, &s_r_opt);
	}

	if (argc > 1)
		usage_with_options(usage_str, options);
}

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
