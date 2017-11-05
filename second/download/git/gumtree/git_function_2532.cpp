static int run_rebase(const unsigned char *curr_head,
		const unsigned char *merge_head,
		const unsigned char *fork_point)
{
	int ret;
	unsigned char oct_merge_base[GIT_SHA1_RAWSZ];
	struct argv_array args = ARGV_ARRAY_INIT;

	if (!get_octopus_merge_base(oct_merge_base, curr_head, merge_head, fork_point))
		if (!is_null_sha1(fork_point) && !hashcmp(oct_merge_base, fork_point))
			fork_point = NULL;

	argv_array_push(&args, "rebase");

	/* Shared options */
	argv_push_verbosity(&args);

	/* Options passed to git-rebase */
	if (opt_rebase == REBASE_PRESERVE)
		argv_array_push(&args, "--preserve-merges");
	else if (opt_rebase == REBASE_INTERACTIVE)
		argv_array_push(&args, "--interactive");
	if (opt_diffstat)
		argv_array_push(&args, opt_diffstat);
	argv_array_pushv(&args, opt_strategies.argv);
	argv_array_pushv(&args, opt_strategy_opts.argv);
	if (opt_gpg_sign)
		argv_array_push(&args, opt_gpg_sign);
	if (opt_autostash == 0)
		argv_array_push(&args, "--no-autostash");
	else if (opt_autostash == 1)
		argv_array_push(&args, "--autostash");
	if (opt_verify_signatures &&
	    !strcmp(opt_verify_signatures, "--verify-signatures"))
		warning(_("ignoring --verify-signatures for rebase"));

	argv_array_push(&args, "--onto");
	argv_array_push(&args, sha1_to_hex(merge_head));

	if (fork_point && !is_null_sha1(fork_point))
		argv_array_push(&args, sha1_to_hex(fork_point));
	else
		argv_array_push(&args, sha1_to_hex(merge_head));

	ret = run_command_v_opt(args.argv, RUN_GIT_CMD);
	argv_array_clear(&args);
	return ret;
}