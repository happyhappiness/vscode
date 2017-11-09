static int do_diff_combined(struct rev_info *opt, struct commit *commit)
{
	diff_tree_combined_merge(commit, opt->dense_combined_merges, opt);
	return !opt->loginfo;
}