void diffcore_std(struct diff_options *options)
{
	/* NOTE please keep the following in sync with diff_tree_combined() */
	if (options->skip_stat_unmatch)
		diffcore_skip_stat_unmatch(options);
	if (!options->found_follow) {
		/* See try_to_follow_renames() in tree-diff.c */
		if (options->break_opt != -1)
			diffcore_break(options->break_opt);
		if (options->detect_rename)
			diffcore_rename(options);
		if (options->break_opt != -1)
			diffcore_merge_broken();
	}
	if (options->pickaxe)
		diffcore_pickaxe(options);
	if (options->orderfile)
		diffcore_order(options->orderfile);
	if (!options->found_follow)
		/* See try_to_follow_renames() in tree-diff.c */
		diff_resolve_rename_copy();
	diffcore_apply_filter(options);

	if (diff_queued_diff.nr && !DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		DIFF_OPT_SET(options, HAS_CHANGES);
	else
		DIFF_OPT_CLR(options, HAS_CHANGES);

	options->found_follow = 0;
}