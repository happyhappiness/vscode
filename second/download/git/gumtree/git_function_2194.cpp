int replace_each_worktree_head_symref(const char *oldref, const char *newref)
{
	int ret = 0;
	struct worktree **worktrees = get_worktrees();
	int i;

	for (i = 0; worktrees[i]; i++) {
		if (worktrees[i]->is_detached)
			continue;
		if (strcmp(oldref, worktrees[i]->head_ref))
			continue;

		if (set_worktree_head_symref(worktrees[i]->git_dir, newref)) {
			ret = -1;
			error(_("HEAD of working tree %s is not updated"),
			      worktrees[i]->path);
		}
	}

	free_worktrees(worktrees);
	return ret;
}