	struct remote *remote;
	int err = 0, complete_refs_before_fetch = 1;

	struct refspec *refspec;
	const char *fetch_pattern;

	packet_trace_identity("clone");
	argc = parse_options(argc, argv, prefix, builtin_clone_options,
			     builtin_clone_usage, 0);

	if (argc > 2)
		usage_msg_opt(_("Too many arguments."),
