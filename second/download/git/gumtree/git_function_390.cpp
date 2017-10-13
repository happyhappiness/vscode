int cmd_status(int argc, const char **argv, const char *prefix)
{
	static struct wt_status s;
	int fd;
	unsigned char sha1[20];
	static struct option builtin_status_options[] = {
		OPT__VERBOSE(&verbose, N_("be verbose")),
		OPT_SET_INT('s', "short", &status_format,
			    N_("show status concisely"), STATUS_FORMAT_SHORT),
		OPT_BOOL('b', "branch", &s.show_branch,
			 N_("show branch information")),
		OPT_SET_INT(0, "porcelain", &status_format,
			    N_("machine-readable output"),
			    STATUS_FORMAT_PORCELAIN),
		OPT_SET_INT(0, "long", &status_format,
			    N_("show status in long format (default)"),
			    STATUS_FORMAT_LONG),
		OPT_BOOL('z', "null", &s.null_termination,
			 N_("terminate entries with NUL")),
		{ OPTION_STRING, 'u', "untracked-files", &untracked_files_arg,
		  N_("mode"),
		  N_("show untracked files, optional modes: all, normal, no. (Default: all)"),
		  PARSE_OPT_OPTARG, NULL, (intptr_t)"all" },
		OPT_BOOL(0, "ignored", &show_ignored_in_status,
			 N_("show ignored files")),
		{ OPTION_STRING, 0, "ignore-submodules", &ignore_submodule_arg, N_("when"),
		  N_("ignore changes to submodules, optional when: all, dirty, untracked. (Default: all)"),
		  PARSE_OPT_OPTARG, NULL, (intptr_t)"all" },
		OPT_COLUMN(0, "column", &s.colopts, N_("list untracked files in columns")),
		OPT_END(),
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_status_usage, builtin_status_options);

	status_init_config(&s, git_status_config);
	argc = parse_options(argc, argv, prefix,
			     builtin_status_options,
			     builtin_status_usage, 0);
	finalize_colopts(&s.colopts, -1);
	finalize_deferred_config(&s);

	handle_untracked_files_arg(&s);
	if (show_ignored_in_status)
		s.show_ignored_files = 1;
	parse_pathspec(&s.pathspec, 0,
		       PATHSPEC_PREFER_FULL,
		       prefix, argv);

	read_cache_preload(&s.pathspec);
	refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED, &s.pathspec, NULL, NULL);

	fd = hold_locked_index(&index_lock, 0);

	s.is_initial = get_sha1(s.reference, sha1) ? 1 : 0;
	s.ignore_submodule_arg = ignore_submodule_arg;
	wt_status_collect(&s);

	if (0 <= fd)
		update_index_if_able(&the_index, &index_lock);

	if (s.relative_paths)
		s.prefix = prefix;

	switch (status_format) {
	case STATUS_FORMAT_SHORT:
		wt_shortstatus_print(&s);
		break;
	case STATUS_FORMAT_PORCELAIN:
		wt_porcelain_print(&s);
		break;
	case STATUS_FORMAT_UNSPECIFIED:
		die("BUG: finalize_deferred_config() should have been called");
		break;
	case STATUS_FORMAT_NONE:
	case STATUS_FORMAT_LONG:
		s.verbose = verbose;
		s.ignore_submodule_arg = ignore_submodule_arg;
		wt_status_print(&s);
		break;
	}
	return 0;
}