int repo_init(struct repository *repo, const char *gitdir, const char *worktree)
{
	struct repository_format format;
	memset(repo, 0, sizeof(*repo));

	repo->ignore_env = 1;

	if (repo_init_gitdir(repo, gitdir))
		goto error;

	if (read_and_verify_repository_format(&format, repo->commondir))
		goto error;

	if (worktree)
		repo_set_worktree(repo, worktree);

	return 0;

error:
	repo_clear(repo);
	return -1;
}