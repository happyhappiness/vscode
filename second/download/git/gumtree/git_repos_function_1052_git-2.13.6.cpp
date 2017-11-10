int has_uncommitted_changes(int ignore_submodules)
{
	struct rev_info rev_info;
	int result;

	if (is_cache_unborn())
		return 0;

	init_revisions(&rev_info, NULL);
	if (ignore_submodules)
		DIFF_OPT_SET(&rev_info.diffopt, IGNORE_SUBMODULES);
	DIFF_OPT_SET(&rev_info.diffopt, QUICK);
	add_head_to_pending(&rev_info);
	diff_setup_done(&rev_info.diffopt);
	result = run_diff_index(&rev_info, 1);
	return diff_result_code(&rev_info.diffopt, result);
}