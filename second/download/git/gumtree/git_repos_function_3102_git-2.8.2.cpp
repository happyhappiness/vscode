static void find_unpushed_submodule_commits(struct commit *commit,
		struct string_list *needs_pushing)
{
	struct rev_info rev;

	init_revisions(&rev, NULL);
	rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
	rev.diffopt.format_callback = collect_submodules_from_diff;
	rev.diffopt.format_callback_data = needs_pushing;
	diff_tree_combined_merge(commit, 1, &rev);
}