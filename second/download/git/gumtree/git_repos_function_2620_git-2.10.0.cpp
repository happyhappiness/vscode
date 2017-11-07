static struct worktree *get_main_worktree(void)
{
	struct worktree *worktree = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf worktree_path = STRBUF_INIT;
	struct strbuf head_ref = STRBUF_INIT;
	int is_bare = 0;
	int is_detached = 0;

	strbuf_add_absolute_path(&worktree_path, get_git_common_dir());
	is_bare = !strbuf_strip_suffix(&worktree_path, "/.git");
	if (is_bare)
		strbuf_strip_suffix(&worktree_path, "/.");

	strbuf_addf(&path, "%s/HEAD", get_git_common_dir());

	if (parse_ref(path.buf, &head_ref, &is_detached) < 0)
		goto done;

	worktree = xmalloc(sizeof(struct worktree));
	worktree->path = strbuf_detach(&worktree_path, NULL);
	worktree->id = NULL;
	worktree->is_bare = is_bare;
	worktree->head_ref = NULL;
	worktree->is_detached = is_detached;
	worktree->is_current = 0;
	add_head_info(&head_ref, worktree);
	worktree->lock_reason = NULL;
	worktree->lock_reason_valid = 0;

done:
	strbuf_release(&path);
	strbuf_release(&worktree_path);
	strbuf_release(&head_ref);
	return worktree;
}