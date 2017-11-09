int has_unstaged_changes(int ignore_submodules)
{
	struct rev_info rev_info;
	int result;

	init_revisions(&rev_info, NULL);
	if (ignore_submodules)
		DIFF_OPT_SET(&rev_info.diffopt, IGNORE_SUBMODULES);
	DIFF_OPT_SET(&rev_info.diffopt, QUICK);
	diff_setup_done(&rev_info.diffopt);
	result = run_diff_files(&rev_info, 0);
	return diff_result_code(&rev_info.diffopt, result);
}