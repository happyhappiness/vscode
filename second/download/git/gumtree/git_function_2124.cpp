static int add(int ac, const char **av, const char *prefix)
{
	int force = 0, detach = 0;
	const char *new_branch = NULL, *new_branch_force = NULL;
	const char *path, *branch;
	struct argv_array cmd = ARGV_ARRAY_INIT;
	struct option options[] = {
		OPT__FORCE(&force, N_("checkout <branch> even if already checked out in other worktree")),
		OPT_STRING('b', NULL, &new_branch, N_("branch"),
			   N_("create a new branch")),
		OPT_STRING('B', NULL, &new_branch_force, N_("branch"),
			   N_("create or reset a branch")),
		OPT_BOOL(0, "detach", &detach, N_("detach HEAD at named commit")),
		OPT_END()
	};

	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (new_branch && new_branch_force)
		die(_("-b and -B are mutually exclusive"));
	if (ac < 1 || ac > 2)
		usage_with_options(worktree_usage, options);

	path = prefix ? prefix_filename(prefix, strlen(prefix), av[0]) : av[0];
	branch = ac < 2 ? "HEAD" : av[1];

	if (ac < 2 && !new_branch && !new_branch_force) {
		int n;
		const char *s = worktree_basename(path, &n);
		new_branch = xstrndup(s, n);
	}

	argv_array_push(&cmd, "checkout");
	if (force)
		argv_array_push(&cmd, "--ignore-other-worktrees");
	if (new_branch)
		argv_array_pushl(&cmd, "-b", new_branch, NULL);
	if (new_branch_force)
		argv_array_pushl(&cmd, "-B", new_branch_force, NULL);
	if (detach)
		argv_array_push(&cmd, "--detach");
	argv_array_push(&cmd, branch);

	return add_worktree(path, cmd.argv);
}