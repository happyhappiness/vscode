static int unlock_worktree(int ac, const char **av, const char *prefix)
{
	struct option options[] = {
		OPT_END()
	};
	struct worktree **worktrees, *wt;
	int ret;

	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (ac != 1)
		usage_with_options(worktree_usage, options);

	worktrees = get_worktrees();
	wt = find_worktree(worktrees, prefix, av[0]);
	if (!wt)
		die(_("'%s' is not a working tree"), av[0]);
	if (is_main_worktree(wt))
		die(_("The main working tree cannot be locked or unlocked"));
	if (!is_worktree_locked(wt))
		die(_("'%s' is not locked"), av[0]);
	ret = unlink_or_warn(git_common_path("worktrees/%s/locked", wt->id));
	free_worktrees(worktrees);
	return ret;
}