static int evaluate_result(void)
{
	int cnt = 0;
	struct rev_info rev;

	/* Check how many files differ. */
	init_revisions(&rev, "");
	setup_revisions(0, NULL, &rev, NULL);
	rev.diffopt.output_format |=
		DIFF_FORMAT_CALLBACK;
	rev.diffopt.format_callback = count_diff_files;
	rev.diffopt.format_callback_data = &cnt;
	run_diff_files(&rev, 0);

	/*
	 * Check how many unmerged entries are
	 * there.
	 */
	cnt += count_unmerged_entries();

	return cnt;
}