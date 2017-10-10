
	argc = parse_options(argc, argv, prefix, options, merge_file_usage, 0);
	if (argc != 3)
		usage_with_options(merge_file_usage, options);
	if (quiet) {
		if (!freopen("/dev/null", "w", stderr))
			return error_errno("failed to redirect stderr to /dev/null");
	}

	if (prefix)
		prefixlen = strlen(prefix);

	for (i = 0; i < 3; i++) {
