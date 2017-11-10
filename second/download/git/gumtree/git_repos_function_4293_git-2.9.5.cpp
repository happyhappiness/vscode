static int has_unstaged_changes(const char *prefix)
{
	struct rev_info rev_info;
	int result;

	init_revisions(&rev_info, prefix);
	DIFF_OPT_SET(&rev_info.diffopt, IGNORE_SUBMODULES);
	DIFF_OPT_SET(&rev_info.diffopt, QUICK);
	diff_setup_done(&rev_info.diffopt);
	result = run_diff_files(&rev_info, 0);
	return diff_result_code(&rev_info.diffopt, result);
}