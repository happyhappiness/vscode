static void mark_current_worktree(struct worktree **worktrees)
{
	char *git_dir = absolute_pathdup(get_git_dir());
	int i;

	for (i = 0; worktrees[i]; i++) {
		struct worktree *wt = worktrees[i];
		const char *wt_git_dir = get_worktree_git_dir(wt);

		if (!fspathcmp(git_dir, absolute_path(wt_git_dir))) {
			wt->is_current = 1;
			break;
		}
	}
	free(git_dir);
}