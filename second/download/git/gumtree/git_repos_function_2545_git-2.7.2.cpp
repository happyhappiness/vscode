static struct worktree *get_linked_worktree(const char *id)
{
	struct worktree *worktree = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf worktree_path = STRBUF_INIT;
	struct strbuf gitdir = STRBUF_INIT;
	struct strbuf head_ref = STRBUF_INIT;
	int is_detached = 0;

	if (!id)
		die("Missing linked worktree name");

	strbuf_addf(&gitdir, "%s/worktrees/%s",
			absolute_path(get_git_common_dir()), id);
	strbuf_addf(&path, "%s/gitdir", gitdir.buf);
	if (strbuf_read_file(&worktree_path, path.buf, 0) <= 0)
		/* invalid gitdir file */
		goto done;

	strbuf_rtrim(&worktree_path);
	if (!strbuf_strip_suffix(&worktree_path, "/.git")) {
		strbuf_reset(&worktree_path);
		strbuf_addstr(&worktree_path, absolute_path("."));
		strbuf_strip_suffix(&worktree_path, "/.");
	}

	strbuf_reset(&path);
	strbuf_addf(&path, "%s/worktrees/%s/HEAD", get_git_common_dir(), id);

	if (parse_ref(path.buf, &head_ref, &is_detached) < 0)
		goto done;

	worktree = xmalloc(sizeof(struct worktree));
	worktree->path = strbuf_detach(&worktree_path, NULL);
	worktree->git_dir = strbuf_detach(&gitdir, NULL);
	worktree->is_bare = 0;
	worktree->head_ref = NULL;
	worktree->is_detached = is_detached;
	add_head_info(&head_ref, worktree);

done:
	strbuf_release(&path);
	strbuf_release(&gitdir);
	strbuf_release(&worktree_path);
	strbuf_release(&head_ref);
	return worktree;
}