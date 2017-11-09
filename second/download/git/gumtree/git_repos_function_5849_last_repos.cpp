int cmd_verify_pack(int argc, const char **argv, const char *prefix)
{
	int err = 0;
	unsigned int flags = 0;
	int i;
	const struct option verify_pack_options[] = {
		OPT_BIT('v', "verbose", &flags, N_("verbose"),
			VERIFY_PACK_VERBOSE),
		OPT_BIT('s', "stat-only", &flags, N_("show statistics only"),
			VERIFY_PACK_STAT_ONLY),
		OPT_END()
	};

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, verify_pack_options,
			     verify_pack_usage, 0);
	if (argc < 1)
		usage_with_options(verify_pack_usage, verify_pack_options);
	for (i = 0; i < argc; i++) {
		if (verify_one_pack(argv[i], flags))
			err = 1;
	}

	return err;
}