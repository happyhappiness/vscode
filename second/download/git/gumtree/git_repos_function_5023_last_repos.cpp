static int run_merge(void)
{
	int ret;
	struct argv_array args = ARGV_ARRAY_INIT;

	argv_array_pushl(&args, "merge", NULL);

	/* Shared options */
	argv_push_verbosity(&args);
	if (opt_progress)
		argv_array_push(&args, opt_progress);

	/* Options passed to git-merge */
	if (opt_diffstat)
		argv_array_push(&args, opt_diffstat);
	if (opt_log)
		argv_array_push(&args, opt_log);
	if (opt_squash)
		argv_array_push(&args, opt_squash);
	if (opt_commit)
		argv_array_push(&args, opt_commit);
	if (opt_edit)
		argv_array_push(&args, opt_edit);
	if (opt_ff)
		argv_array_push(&args, opt_ff);
	if (opt_verify_signatures)
		argv_array_push(&args, opt_verify_signatures);
	argv_array_pushv(&args, opt_strategies.argv);
	argv_array_pushv(&args, opt_strategy_opts.argv);
	if (opt_gpg_sign)
		argv_array_push(&args, opt_gpg_sign);
	if (opt_allow_unrelated_histories > 0)
		argv_array_push(&args, "--allow-unrelated-histories");

	argv_array_push(&args, "FETCH_HEAD");
	ret = run_command_v_opt(args.argv, RUN_GIT_CMD);
	argv_array_clear(&args);
	return ret;
}