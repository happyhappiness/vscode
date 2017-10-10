
	/* With no flags, we default to showing the cached files */
	if (!(show_stage || show_deleted || show_others || show_unmerged ||
	      show_killed || show_modified || show_resolve_undo))
		show_cached = 1;

	prune_cache(max_prefix, max_prefix_len);
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
