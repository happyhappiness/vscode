	};

	argc = parse_options(argc, argv, prefix, options, stripspace_usage, 0);
	if (argc)
		usage_with_options(stripspace_usage, options);

	if (mode == STRIP_COMMENTS || mode == COMMENT_LINES)
		git_config(git_default_config, NULL);

	if (strbuf_read(&buf, 0, 1024) < 0)
		die_errno("could not read the input");

	if (mode == STRIP_DEFAULT || mode == STRIP_COMMENTS)
		strbuf_stripspace(&buf, mode == STRIP_COMMENTS);
