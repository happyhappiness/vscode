static struct worktree *get_main_worktree(void)
{
	struct worktree *worktree = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf worktree_path = STRBUF_INIT;
	int is_bare = 0;

	strbuf_add_absolute_path(&worktree_path, get_git_common_dir());
	is_bare = !strbuf_strip_suffix(&worktree_path, "/.git");
	if (is_bare)
		strbuf_strip_suffix(&worktree_path, "/.");

	strbuf_addf(&path, "%s/HEAD", get_git_common_dir());

	worktree = xcalloc(1, sizeof(*worktree));
	worktree->path = strbuf_detach(&worktree_path, NULL);
	worktree->is_bare = is_bare;
	add_head_info(worktree);

	strbuf_release(&path);
	strbuf_release(&worktree_path);
	return worktree;
}