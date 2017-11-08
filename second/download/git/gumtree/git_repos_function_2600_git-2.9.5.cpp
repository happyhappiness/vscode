static void mark_current_worktree(struct worktree **worktrees)
{
	struct strbuf git_dir = STRBUF_INIT;
	struct strbuf path = STRBUF_INIT;
	int i;

	strbuf_addstr(&git_dir, absolute_path(get_git_dir()));
	for (i = 0; worktrees[i]; i++) {
		struct worktree *wt = worktrees[i];
		strbuf_addstr(&path, absolute_path(get_worktree_git_dir(wt)));
		wt->is_current = !fspathcmp(git_dir.buf, path.buf);
		strbuf_reset(&path);
		if (wt->is_current)
			break;
	}
	strbuf_release(&git_dir);
	strbuf_release(&path);
}