int cmd_describe(int argc, const char **argv, const char *prefix)
{
	int contains = 0;
	struct option options[] = {
		OPT_BOOL(0, "contains",   &contains, N_("find the tag that comes after the commit")),
		OPT_BOOL(0, "debug",      &debug, N_("debug search strategy on stderr")),
		OPT_BOOL(0, "all",        &all, N_("use any ref")),
		OPT_BOOL(0, "tags",       &tags, N_("use any tag, even unannotated")),
		OPT_BOOL(0, "long",       &longformat, N_("always use long format")),
		OPT_BOOL(0, "first-parent", &first_parent, N_("only follow first parent")),
		OPT__ABBREV(&abbrev),
		OPT_SET_INT(0, "exact-match", &max_candidates,
			    N_("only output exact matches"), 0),
		OPT_INTEGER(0, "candidates", &max_candidates,
			    N_("consider <n> most recent tags (default: 10)")),
		OPT_STRING(0, "match",       &pattern, N_("pattern"),
			   N_("only consider tags matching <pattern>")),
		OPT_BOOL(0, "always",        &always,
			N_("show abbreviated commit object as fallback")),
		{OPTION_STRING, 0, "dirty",  &dirty, N_("mark"),
			N_("append <mark> on dirty working tree (default: \"-dirty\")"),
			PARSE_OPT_OPTARG, NULL, (intptr_t) "-dirty"},
		OPT_END(),
	};

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, options, describe_usage, 0);
	if (abbrev < 0)
		abbrev = DEFAULT_ABBREV;

	if (max_candidates < 0)
		max_candidates = 0;
	else if (max_candidates > MAX_TAGS)
		max_candidates = MAX_TAGS;

	save_commit_buffer = 0;

	if (longformat && abbrev == 0)
		die(_("--long is incompatible with --abbrev=0"));

	if (contains) {
		struct argv_array args;

		argv_array_init(&args);
		argv_array_pushl(&args, "name-rev",
				 "--peel-tag", "--name-only", "--no-undefined",
				 NULL);
		if (always)
			argv_array_push(&args, "--always");
		if (!all) {
			argv_array_push(&args, "--tags");
			if (pattern)
				argv_array_pushf(&args, "--refs=refs/tags/%s", pattern);
		}
		if (argc)
			argv_array_pushv(&args, argv);
		else
			argv_array_push(&args, "HEAD");
		return cmd_name_rev(args.argc, args.argv, prefix);
	}

	hashmap_init(&names, (hashmap_cmp_fn) commit_name_cmp, 0);
	for_each_rawref(get_name, NULL);
	if (!names.size && !always)
		die(_("No names found, cannot describe anything."));

	if (argc == 0) {
		if (dirty) {
			static struct lock_file index_lock;
			int fd;

			read_cache_preload(NULL);
			refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED,
				      NULL, NULL, NULL);
			fd = hold_locked_index(&index_lock, 0);
			if (0 <= fd)
				update_index_if_able(&the_index, &index_lock);

			if (!cmd_diff_index(ARRAY_SIZE(diff_index_args) - 1,
					    diff_index_args, prefix))
				dirty = NULL;
		}
		describe("HEAD", 1);
	} else if (dirty) {
		die(_("--dirty is incompatible with commit-ishes"));
	} else {
		while (argc-- > 0)
			describe(*argv++, argc == 0);
	}
	return 0;
}