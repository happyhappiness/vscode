int cmd_hash_object(int argc, const char **argv, const char *prefix)
{
	static const char * const hash_object_usage[] = {
		N_("git hash-object [-t <type>] [-w] [--path=<file>|--no-filters] [--stdin] [--] <file>..."),
		N_("git hash-object  --stdin-paths < <list-of-paths>"),
		NULL
	};
	const char *type = blob_type;
	int hashstdin = 0;
	int stdin_paths = 0;
	int no_filters = 0;
	int literally = 0;
	unsigned flags = HASH_FORMAT_CHECK;
	const char *vpath = NULL;
	const struct option hash_object_options[] = {
		OPT_STRING('t', NULL, &type, N_("type"), N_("object type")),
		OPT_BIT('w', NULL, &flags, N_("write the object into the object database"),
			HASH_WRITE_OBJECT),
		OPT_COUNTUP( 0 , "stdin", &hashstdin, N_("read the object from stdin")),
		OPT_BOOL( 0 , "stdin-paths", &stdin_paths, N_("read file names from stdin")),
		OPT_BOOL( 0 , "no-filters", &no_filters, N_("store file as is without filters")),
		OPT_BOOL( 0, "literally", &literally, N_("just hash any random garbage to create corrupt objects for debugging Git")),
		OPT_STRING( 0 , "path", &vpath, N_("file"), N_("process file as it were from this path")),
		OPT_END()
	};
	int i;
	int prefix_length = -1;
	const char *errstr = NULL;

	argc = parse_options(argc, argv, NULL, hash_object_options,
			     hash_object_usage, 0);

	if (flags & HASH_WRITE_OBJECT) {
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
		hash_fd(0, type, vpath, flags, literally);

	for (i = 0 ; i < argc; i++) {
		const char *arg = argv[i];

		if (0 <= prefix_length)
			arg = prefix_filename(prefix, prefix_length, arg);
		hash_object(arg, type, no_filters ? NULL : vpath ? vpath : arg,
			    flags, literally);
	}

	if (stdin_paths)
		hash_stdin_paths(type, no_filters, flags, literally);

	return 0;
}