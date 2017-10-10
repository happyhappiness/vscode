		argv_array_push(&args, "--autostash");
	if (opt_verify_signatures &&
	    !strcmp(opt_verify_signatures, "--verify-signatures"))
		warning(_("ignoring --verify-signatures for rebase"));

	argv_array_push(&args, "--onto");
	argv_array_push(&args, oid_to_hex(merge_head));

	if (fork_point && !is_null_oid(fork_point))
		argv_array_push(&args, oid_to_hex(fork_point));
	else
		argv_array_push(&args, oid_to_hex(merge_head));

	ret = run_command_v_opt(args.argv, RUN_GIT_CMD);
	argv_array_clear(&args);
	return ret;
}

int cmd_pull(int argc, const char **argv, const char *prefix)
{
	const char *repo, **refspecs;
	struct oid_array merge_heads = OID_ARRAY_INIT;
	struct object_id orig_head, curr_head;
	struct object_id rebase_fork_point;

	if (!getenv("GIT_REFLOG_ACTION"))
		set_reflog_message(argc, argv);

	argc = parse_options(argc, argv, prefix, pull_options, pull_usage, 0);

