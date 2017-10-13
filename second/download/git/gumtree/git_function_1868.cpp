int cmd_cat_file(int argc, const char **argv, const char *prefix)
{
	int opt = 0;
	const char *exp_type = NULL, *obj_name = NULL;
	struct batch_options batch = {0};
	int unknown_type = 0;

	const struct option options[] = {
		OPT_GROUP(N_("<type> can be one of: blob, tree, commit, tag")),
		OPT_CMDMODE('t', NULL, &opt, N_("show object type"), 't'),
		OPT_CMDMODE('s', NULL, &opt, N_("show object size"), 's'),
		OPT_CMDMODE('e', NULL, &opt,
			    N_("exit with zero when there's no error"), 'e'),
		OPT_CMDMODE('p', NULL, &opt, N_("pretty-print object's content"), 'p'),
		OPT_CMDMODE(0, "textconv", &opt,
			    N_("for blob objects, run textconv on object's content"), 'c'),
		OPT_BOOL( 0, "allow-unknown-type", &unknown_type,
			  N_("allow -s and -t to work with broken/corrupt objects")),
		{ OPTION_CALLBACK, 0, "batch", &batch, "format",
			N_("show info and content of objects fed from the standard input"),
			PARSE_OPT_OPTARG, batch_option_callback },
		{ OPTION_CALLBACK, 0, "batch-check", &batch, "format",
			N_("show info about objects fed from the standard input"),
			PARSE_OPT_OPTARG, batch_option_callback },
		OPT_BOOL(0, "follow-symlinks", &batch.follow_symlinks,
			 N_("follow in-tree symlinks (used with --batch or --batch-check)")),
		OPT_END()
	};

	git_config(git_cat_file_config, NULL);

	argc = parse_options(argc, argv, prefix, options, cat_file_usage, 0);

	if (opt) {
		if (argc == 1)
			obj_name = argv[0];
		else
			usage_with_options(cat_file_usage, options);
	}
	if (!opt && !batch.enabled) {
		if (argc == 2) {
			exp_type = argv[0];
			obj_name = argv[1];
		} else
			usage_with_options(cat_file_usage, options);
	}
	if (batch.enabled && (opt || argc)) {
		usage_with_options(cat_file_usage, options);
	}

	if (batch.follow_symlinks && !batch.enabled) {
		usage_with_options(cat_file_usage, options);
	}

	if (batch.enabled)
		return batch_objects(&batch);

	if (unknown_type && opt != 't' && opt != 's')
		die("git cat-file --allow-unknown-type: use with -s or -t");
	return cat_one_file(opt, exp_type, obj_name, unknown_type);
}