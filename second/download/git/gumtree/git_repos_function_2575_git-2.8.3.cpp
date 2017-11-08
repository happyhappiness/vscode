void free_worktrees(struct worktree **worktrees)
{
	int i = 0;

	for (i = 0; worktrees[i]; i++) {
		free(worktrees[i]->path);
		free(worktrees[i]->git_dir);
		free(worktrees[i]->head_ref);
		free(worktrees[i]);
	}
	free (worktrees);
}