	N_("git checkout-index [<options>] [--] [<file>...]"),
	NULL
};

static struct lock_file lock_file;

static int option_parse_stage(const struct option *opt,
			      const char *arg, int unset)
{
	if (!strcmp(arg, "all")) {
		to_tempfile = 1;
		checkout_stage = CHECKOUT_ALL;
	} else {
		int ch = arg[0];
		if ('1' <= ch && ch <= '3')
			checkout_stage = arg[0] - '0';
		else
			die(_("stage should be between 1 and 3 or all"));
	}
	return 0;
}

int cmd_checkout_index(int argc, const char **argv, const char *prefix)
{
	int i;
	int newfd = -1;
	int all = 0;
	int read_from_stdin = 0;
	int prefix_length;
	int force = 0, quiet = 0, not_new = 0;
	int index_opt = 0;
	struct option builtin_checkout_index_options[] = {
		OPT_BOOL('a', "all", &all,
			N_("check out all files in the index")),
		OPT__FORCE(&force, N_("force overwrite of existing files")),
		OPT__QUIET(&quiet,
			N_("no warning for existing files and files not in index")),
		OPT_BOOL('n', "no-create", &not_new,
			N_("don't checkout new files")),
		OPT_BOOL('u', "index", &index_opt,
			 N_("update stat information in the index file")),
		OPT_BOOL('z', NULL, &nul_term_line,
			N_("paths are separated with NUL character")),
		OPT_BOOL(0, "stdin", &read_from_stdin,
			N_("read list of paths from the standard input")),
		OPT_BOOL(0, "temp", &to_tempfile,
			N_("write the content to temporary files")),
		OPT_STRING(0, "prefix", &state.base_dir, N_("string"),
			N_("when creating files, prepend <string>")),
		{ OPTION_CALLBACK, 0, "stage", NULL, "1-3|all",
			N_("copy out the files from named stage"),
			PARSE_OPT_NONEG, option_parse_stage },
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_checkout_index_usage,
				   builtin_checkout_index_options);
	git_config(git_default_config, NULL);
	prefix_length = prefix ? strlen(prefix) : 0;

	if (read_cache() < 0) {
		die("invalid cache");
	}

	argc = parse_options(argc, argv, prefix, builtin_checkout_index_options,
			builtin_checkout_index_usage, 0);
	state.force = force;
	state.quiet = quiet;
	state.not_new = not_new;

	if (!state.base_dir)
		state.base_dir = "";
	state.base_dir_len = strlen(state.base_dir);

	/*
	 * when --prefix is specified we do not want to update cache.
	 */
	if (index_opt && !state.base_dir_len && !to_tempfile) {
		state.refresh_cache = 1;
		state.istate = &the_index;
		newfd = hold_locked_index(&lock_file, 1);
	}

	/* Check out named files first */
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		char *p;
