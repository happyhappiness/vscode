	grep_commit_pattern_type(GREP_PATTERN_TYPE_UNSPECIFIED,
				 &revs->grep_filter);
	compile_grep_patterns(&revs->grep_filter);

	if (revs->reverse && revs->reflog_info)
		die("cannot combine --reverse with --walk-reflogs");
	if (revs->rewrite_parents && revs->children.name)
		die("cannot combine --parents and --children");

	/*
	 * Limitations on the graph functionality
	 */
