static int cmd_log_walk(struct rev_info *rev)
{
	struct commit *commit;
	int saved_nrl = 0;
	int saved_dcctc = 0, close_file = rev->diffopt.close_file;

	if (rev->early_output)
		setup_early_output(rev);

	if (prepare_revision_walk(rev))
		die(_("revision walk setup failed"));

	if (rev->early_output)
		finish_early_output(rev);

	/*
	 * For --check and --exit-code, the exit code is based on CHECK_FAILED
	 * and HAS_CHANGES being accumulated in rev->diffopt, so be careful to
	 * retain that state information if replacing rev->diffopt in this loop
	 */
	rev->diffopt.close_file = 0;
	while ((commit = get_revision(rev)) != NULL) {
		if (!log_tree_commit(rev, commit) && rev->max_count >= 0)
			/*
			 * We decremented max_count in get_revision,
			 * but we didn't actually show the commit.
			 */
			rev->max_count++;
		if (!rev->reflog_info) {
			/*
			 * We may show a given commit multiple times when
			 * walking the reflogs.
			 */
			free_commit_buffer(commit);
			free_commit_list(commit->parents);
			commit->parents = NULL;
		}
		if (saved_nrl < rev->diffopt.needed_rename_limit)
			saved_nrl = rev->diffopt.needed_rename_limit;
		if (rev->diffopt.degraded_cc_to_c)
			saved_dcctc = 1;
	}
	rev->diffopt.degraded_cc_to_c = saved_dcctc;
	rev->diffopt.needed_rename_limit = saved_nrl;
	if (close_file)
		fclose(rev->diffopt.file);

	if (rev->diffopt.output_format & DIFF_FORMAT_CHECKDIFF &&
	    DIFF_OPT_TST(&rev->diffopt, CHECK_FAILED)) {
		return 02;
	}
	return diff_result_code(&rev->diffopt, 0);
}