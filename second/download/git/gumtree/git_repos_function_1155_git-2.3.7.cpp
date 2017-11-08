void setup_diff_pager(struct diff_options *opt)
{
	/*
	 * If the user asked for our exit code, then either they want --quiet
	 * or --exit-code. We should definitely not bother with a pager in the
	 * former case, as we will generate no output. Since we still properly
	 * report our exit code even when a pager is run, we _could_ run a
	 * pager with --exit-code. But since we have not done so historically,
	 * and because it is easy to find people oneline advising "git diff
	 * --exit-code" in hooks and other scripts, we do not do so.
	 */
	if (!DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&
	    check_pager_config("diff") != 0)
		setup_pager();
}