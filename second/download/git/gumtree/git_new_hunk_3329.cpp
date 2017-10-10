	unlink(git_path_merge_rr());
	unlink(git_path_merge_msg());
	unlink(git_path_merge_mode());
	unlink(git_path_squash_msg());
}

void die_if_checked_out(const char *branch, int ignore_current_worktree)
{
	const struct worktree *wt;

	wt = find_shared_symref("HEAD", branch);
	if (!wt || (ignore_current_worktree && wt->is_current))
		return;
	skip_prefix(branch, "refs/heads/", &branch);
	die(_("'%s' is already checked out at '%s'"),
	    branch, wt->path);
}

int replace_each_worktree_head_symref(const char *oldref, const char *newref)
{
	int ret = 0;
	struct worktree **worktrees = get_worktrees();
