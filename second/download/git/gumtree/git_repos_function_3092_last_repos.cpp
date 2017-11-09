static struct worktree *get_linked_worktree(const char *id)
{
	struct worktree *worktree = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf worktree_path = STRBUF_INIT;

	if (!id)
		die("Missing linked worktree name");

	strbuf_git_common_path(&path, the_repository, "worktrees/%s/gitdir", id);
	if (strbuf_read_file(&worktree_path, path.buf, 0) <= 0)
		/* invalid gitdir file */
		goto done;

	strbuf_rtrim(&worktree_path);
	if (!strbuf_strip_suffix(&worktree_path, "/.git")) {
		strbuf_reset(&worktree_path);
		strbuf_add_absolute_path(&worktree_path, ".");
		strbuf_strip_suffix(&worktree_path, "/.");
	}

	strbuf_reset(&path);
	strbuf_addf(&path, "%s/worktrees/%s/HEAD", get_git_common_dir(), id);

	worktree = xcalloc(1, sizeof(*worktree));
	worktree->path = strbuf_detach(&worktree_path, NULL);
	worktree->id = xstrdup(id);
	add_head_info(worktree);

done:
	strbuf_release(&path);
	strbuf_release(&worktree_path);
	return worktree;
}