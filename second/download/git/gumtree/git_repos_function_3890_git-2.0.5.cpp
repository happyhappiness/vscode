int cmd_checkout_index(int argc, const char **argv, const char *prefix)
{
	int i;
	int newfd = -1;
	int all = 0;
	int read_from_stdin = 0;
	int prefix_length;
	int force = 0, quiet = 0, not_new = 0;
	struct option builtin_checkout_index_options[] = {
		OPT_BOOL('a', "all", &all,
			N_("check out all files in the index")),
		OPT__FORCE(&force, N_("force overwrite of existing files")),
		OPT__QUIET(&quiet,
			N_("no warning for existing files and files not in index")),
		OPT_BOOL('n', "no-create", &not_new,
			N_("don't checkout new files")),
		{ OPTION_CALLBACK, 'u', "index", &newfd, NULL,
			N_("update stat information in the index file"),
			PARSE_OPT_NOARG, option_parse_u },
		{ OPTION_CALLBACK, 'z', NULL, NULL, NULL,
			N_("paths are separated with NUL character"),
			PARSE_OPT_NOARG, option_parse_z },
		OPT_BOOL(0, "stdin", &read_from_stdin,
			N_("read list of paths from the standard input")),
		OPT_BOOL(0, "temp", &to_tempfile,
			N_("write the content to temporary files")),
		OPT_CALLBACK(0, "prefix", NULL, N_("string"),
			N_("when creating files, prepend <string>"),
			option_parse_prefix),
		OPT_CALLBACK(0, "stage", NULL, NULL,
			N_("copy out the files from named stage"),
			option_parse_stage),
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_checkout_index_usage,
				   builtin_checkout_index_options);
	git_config(git_default_config, NULL);
	state.base_dir = "";
	prefix_length = prefix ? strlen(prefix) : 0;

	if (read_cache() < 0) {
		die("invalid cache");
	}

	argc = parse_options(argc, argv, prefix, builtin_checkout_index_options,
			builtin_checkout_index_usage, 0);
	state.force = force;
	state.quiet = quiet;
	state.not_new = not_new;

	if (state.base_dir_len || to_tempfile) {
		/* when --prefix is specified we do not
		 * want to update cache.
		 */
		if (state.refresh_cache) {
			rollback_lock_file(&lock_file);
			newfd = -1;
		}
		state.refresh_cache = 0;
	}

	/* Check out named files first */
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		const char *p;

		if (all)
			die("git checkout-index: don't mix '--all' and explicit filenames");
		if (read_from_stdin)
			die("git checkout-index: don't mix '--stdin' and explicit filenames");
		p = prefix_path(prefix, prefix_length, arg);
		checkout_file(p, prefix_length);
		if (p < arg || p > arg + strlen(arg))
			free((char *)p);
	}

	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT, nbuf = STRBUF_INIT;

		if (all)
			die("git checkout-index: don't mix '--all' and '--stdin'");

		while (strbuf_getline(&buf, stdin, line_termination) != EOF) {
			const char *p;
			if (line_termination && buf.buf[0] == '"') {
				strbuf_reset(&nbuf);
				if (unquote_c_style(&nbuf, buf.buf, NULL))
					die("line is badly quoted");
				strbuf_swap(&buf, &nbuf);
			}
			p = prefix_path(prefix, prefix_length, buf.buf);
			checkout_file(p, prefix_length);
			if (p < buf.buf || p > buf.buf + buf.len)
				free((char *)p);
		}
		strbuf_release(&nbuf);
		strbuf_release(&buf);
	}

	if (all)
		checkout_all(prefix, prefix_length);

	if (0 <= newfd &&
	    (write_cache(newfd, active_cache, active_nr) ||
	     commit_locked_index(&lock_file)))
		die("Unable to write new index file");
	return 0;
}