int cmd_ls_files(int argc, const char **argv, const char *cmd_prefix)
{
	int require_work_tree = 0, show_tag = 0, i;
	const char *max_prefix;
	struct dir_struct dir;
	struct exclude_list *el;
	struct string_list exclude_list = STRING_LIST_INIT_NODUP;
	struct option builtin_ls_files_options[] = {
		/* Think twice before adding "--nul" synonym to this */
		OPT_SET_INT('z', NULL, &line_terminator,
			N_("paths are separated with NUL character"), '\0'),
		OPT_BOOL('t', NULL, &show_tag,
			N_("identify the file status with tags")),
		OPT_BOOL('v', NULL, &show_valid_bit,
			N_("use lowercase letters for 'assume unchanged' files")),
		OPT_BOOL('c', "cached", &show_cached,
			N_("show cached files in the output (default)")),
		OPT_BOOL('d', "deleted", &show_deleted,
			N_("show deleted files in the output")),
		OPT_BOOL('m', "modified", &show_modified,
			N_("show modified files in the output")),
		OPT_BOOL('o', "others", &show_others,
			N_("show other files in the output")),
		OPT_BIT('i', "ignored", &dir.flags,
			N_("show ignored files in the output"),
			DIR_SHOW_IGNORED),
		OPT_BOOL('s', "stage", &show_stage,
			N_("show staged contents' object name in the output")),
		OPT_BOOL('k', "killed", &show_killed,
			N_("show files on the filesystem that need to be removed")),
		OPT_BIT(0, "directory", &dir.flags,
			N_("show 'other' directories' names only"),
			DIR_SHOW_OTHER_DIRECTORIES),
		OPT_BOOL(0, "eol", &show_eol, N_("show line endings of files")),
		OPT_NEGBIT(0, "empty-directory", &dir.flags,
			N_("don't show empty directories"),
			DIR_HIDE_EMPTY_DIRECTORIES),
		OPT_BOOL('u', "unmerged", &show_unmerged,
			N_("show unmerged files in the output")),
		OPT_BOOL(0, "resolve-undo", &show_resolve_undo,
			    N_("show resolve-undo information")),
		{ OPTION_CALLBACK, 'x', "exclude", &exclude_list, N_("pattern"),
			N_("skip files matching pattern"),
			0, option_parse_exclude },
		{ OPTION_CALLBACK, 'X', "exclude-from", &dir, N_("file"),
			N_("exclude patterns are read from <file>"),
			0, option_parse_exclude_from },
		OPT_STRING(0, "exclude-per-directory", &dir.exclude_per_dir, N_("file"),
			N_("read additional per-directory exclude patterns in <file>")),
		{ OPTION_CALLBACK, 0, "exclude-standard", &dir, NULL,
			N_("add the standard git exclusions"),
			PARSE_OPT_NOARG, option_parse_exclude_standard },
		{ OPTION_SET_INT, 0, "full-name", &prefix_len, NULL,
			N_("make the output relative to the project top directory"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL },
		OPT_BOOL(0, "recurse-submodules", &recurse_submodules,
			N_("recurse through submodules")),
		OPT_BOOL(0, "error-unmatch", &error_unmatch,
			N_("if any <file> is not in the index, treat this as an error")),
		OPT_STRING(0, "with-tree", &with_tree, N_("tree-ish"),
			N_("pretend that paths removed since <tree-ish> are still present")),
		OPT__ABBREV(&abbrev),
		OPT_BOOL(0, "debug", &debug_mode, N_("show debugging data")),
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(ls_files_usage, builtin_ls_files_options);

	memset(&dir, 0, sizeof(dir));
	prefix = cmd_prefix;
	if (prefix)
		prefix_len = strlen(prefix);
	super_prefix = get_super_prefix();
	git_config(git_default_config, NULL);

	if (read_cache() < 0)
		die("index file corrupt");

	argc = parse_options(argc, argv, prefix, builtin_ls_files_options,
			ls_files_usage, 0);
	el = add_exclude_list(&dir, EXC_CMDL, "--exclude option");
	for (i = 0; i < exclude_list.nr; i++) {
		add_exclude(exclude_list.items[i].string, "", 0, el, --exclude_args);
	}
	if (show_tag || show_valid_bit) {
		tag_cached = "H ";
		tag_unmerged = "M ";
		tag_removed = "R ";
		tag_modified = "C ";
		tag_other = "? ";
		tag_killed = "K ";
		tag_skip_worktree = "S ";
		tag_resolve_undo = "U ";
	}
	if (show_modified || show_others || show_deleted || (dir.flags & DIR_SHOW_IGNORED) || show_killed)
		require_work_tree = 1;
	if (show_unmerged)
		/*
		 * There's no point in showing unmerged unless
		 * you also show the stage information.
		 */
		show_stage = 1;
	if (dir.exclude_per_dir)
		exc_given = 1;

	if (require_work_tree && !is_inside_work_tree())
		setup_work_tree();

	if (recurse_submodules)
		compile_submodule_options(&dir, show_tag);

	if (recurse_submodules &&
	    (show_stage || show_deleted || show_others || show_unmerged ||
	     show_killed || show_modified || show_resolve_undo || with_tree))
		die("ls-files --recurse-submodules unsupported mode");

	if (recurse_submodules && error_unmatch)
		die("ls-files --recurse-submodules does not support "
		    "--error-unmatch");

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD |
		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP,
		       prefix, argv);

	/*
	 * Find common prefix for all pathspec's
	 * This is used as a performance optimization which unfortunately cannot
	 * be done when recursing into submodules
	 */
	if (recurse_submodules)
		max_prefix = NULL;
	else
		max_prefix = common_prefix(&pathspec);
	max_prefix_len = max_prefix ? strlen(max_prefix) : 0;

	/* Treat unmatching pathspec elements as errors */
	if (pathspec.nr && error_unmatch)
		ps_matched = xcalloc(pathspec.nr, 1);

	if ((dir.flags & DIR_SHOW_IGNORED) && !exc_given)
		die("ls-files --ignored needs some exclude pattern");

	/* With no flags, we default to showing the cached files */
	if (!(show_stage || show_deleted || show_others || show_unmerged ||
	      show_killed || show_modified || show_resolve_undo))
		show_cached = 1;

	if (max_prefix)
		prune_cache(max_prefix);
	if (with_tree) {
		/*
		 * Basic sanity check; show-stages and show-unmerged
		 * would not make any sense with this option.
		 */
		if (show_stage || show_unmerged)
			die("ls-files --with-tree is incompatible with -s or -u");
		overlay_tree_on_cache(with_tree, max_prefix);
	}
	show_files(&dir);
	if (show_resolve_undo)
		show_ru_info();

	if (ps_matched) {
		int bad;
		bad = report_path_error(ps_matched, &pathspec, prefix);
		if (bad)
			fprintf(stderr, "Did you forget to 'git add'?\n");

		return bad ? 1 : 0;
	}

	return 0;
}