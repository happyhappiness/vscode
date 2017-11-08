int cmd_hash_object(int argc, const char **argv, const char *prefix)
{
	int i;
	int prefix_length = -1;
	const char *errstr = NULL;

	type = blob_type;

	argc = parse_options(argc, argv, NULL, hash_object_options,
			     hash_object_usage, 0);

	if (write_object) {
		prefix = setup_git_directory();
		prefix_length = prefix ? strlen(prefix) : 0;
		if (vpath && prefix)
			vpath = prefix_filename(prefix, prefix_length, vpath);
	}

	git_config(git_default_config, NULL);

	if (stdin_paths) {
		if (hashstdin)
			errstr = "Can't use --stdin-paths with --stdin";
		else if (argc)
			errstr = "Can't specify files with --stdin-paths";
		else if (vpath)
			errstr = "Can't use --stdin-paths with --path";
	}
	else {
		if (hashstdin > 1)
			errstr = "Multiple --stdin arguments are not supported";
		if (vpath && no_filters)
			errstr = "Can't use --path with --no-filters";
	}

	if (errstr) {
		error("%s", errstr);
		usage_with_options(hash_object_usage, hash_object_options);
	}

	if (hashstdin)
		hash_fd(0, type, write_object, vpath);

	for (i = 0 ; i < argc; i++) {
		const char *arg = argv[i];

		if (0 <= prefix_length)
			arg = prefix_filename(prefix, prefix_length, arg);
		hash_object(arg, type, write_object,
			    no_filters ? NULL : vpath ? vpath : arg);
	}

	if (stdin_paths)
		hash_stdin_paths(type, write_object);

	return 0;
}