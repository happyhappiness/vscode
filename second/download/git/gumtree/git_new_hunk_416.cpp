		s_r_opt.assume_dashdash = 1;
		argc = setup_revisions(argc, argv, opts->revs, &s_r_opt);
	}

	if (argc > 1)
		usage_with_options(usage_str, options);

	/* These option values will be free()d */
	opts->gpg_sign = xstrdup_or_null(opts->gpg_sign);
	opts->strategy = xstrdup_or_null(opts->strategy);

	if (cmd == 'q')
		return sequencer_remove_state(opts);
	if (cmd == 'c')
		return sequencer_continue(opts);
	if (cmd == 'a')
		return sequencer_rollback(opts);
	return sequencer_pick_revisions(opts);
}

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
