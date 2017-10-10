	if (dir.exclude_per_dir)
		exc_given = 1;

	if (require_work_tree && !is_inside_work_tree())
		setup_work_tree();

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD |
		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP,
		       prefix, argv);

	/* Find common prefix for all pathspec's */
	max_prefix = common_prefix(&pathspec);
	max_prefix_len = max_prefix ? strlen(max_prefix) : 0;

	/* Treat unmatching pathspec elements as errors */
	if (pathspec.nr && error_unmatch)
		ps_matched = xcalloc(pathspec.nr, 1);

