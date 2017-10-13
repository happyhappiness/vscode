tatic void reject_rebase_or_bisect_branch(const char *target)
{
	struct worktree **worktrees = get_worktrees();
	int i;

	for (i = 0; worktrees[i]; i++) {
		struct worktree *wt = worktrees[i];

		if (!wt->is_detached)
			continue;

		if (is_worktree_being_rebased(wt, target))
			die(_("Branch %s is being rebased at %s"),
			    target, wt->path);

		if (is_worktree_being_bisected(wt, target))
			die(_("Branch %s is being bisected at %s"),
			    target, wt->path);
	}

	free_worktrees(worktrees);
}