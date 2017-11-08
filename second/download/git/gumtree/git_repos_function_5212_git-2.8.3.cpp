static int add(int ac, const char **av, const char *prefix)
{
	struct add_opts opts;
	const char *new_branch_force = NULL;
	const char *path, *branch;
	struct option options[] = {
		OPT__FORCE(&opts.force, N_("checkout <branch> even if already checked out in other worktree")),
		OPT_STRING('b', NULL, &opts.new_branch, N_("branch"),
			   N_("create a new branch")),
		OPT_STRING('B', NULL, &new_branch_force, N_("branch"),
			   N_("create or reset a branch")),
		OPT_BOOL(0, "detach", &opts.detach, N_("detach HEAD at named commit")),
		OPT_END()
	};

	memset(&opts, 0, sizeof(opts));
	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (!!opts.detach + !!opts.new_branch + !!new_branch_force > 1)
		die(_("-b, -B, and --detach are mutually exclusive"));
	if (ac < 1 || ac > 2)
		usage_with_options(worktree_usage, options);

	path = prefix ? prefix_filename(prefix, strlen(prefix), av[0]) : av[0];
	branch = ac < 2 ? "HEAD" : av[1];

	opts.force_new_branch = !!new_branch_force;
	if (opts.force_new_branch) {
		struct strbuf symref = STRBUF_INIT;

		opts.new_branch = new_branch_force;

		if (!opts.force &&
		    !strbuf_check_branch_ref(&symref, opts.new_branch) &&
		    ref_exists(symref.buf))
			die_if_checked_out(symref.buf);
		strbuf_release(&symref);
	}

	if (ac < 2 && !opts.new_branch && !opts.detach) {
		int n;
		const char *s = worktree_basename(path, &n);
		opts.new_branch = xstrndup(s, n);
	}

	if (opts.new_branch) {
		struct child_process cp;
		memset(&cp, 0, sizeof(cp));
		cp.git_cmd = 1;
		argv_array_push(&cp.args, "branch");
		if (opts.force_new_branch)
			argv_array_push(&cp.args, "--force");
		argv_array_push(&cp.args, opts.new_branch);
		argv_array_push(&cp.args, branch);
		if (run_command(&cp))
			return -1;
		branch = opts.new_branch;
	}

	return add_worktree(path, branch, &opts);
}