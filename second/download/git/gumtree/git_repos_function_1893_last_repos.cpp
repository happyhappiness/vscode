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