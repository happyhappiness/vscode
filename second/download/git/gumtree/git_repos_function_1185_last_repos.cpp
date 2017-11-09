void repo_set_gitdir(struct repository *repo, const char *path)
{
	const char *gitfile = read_gitfile(path);

	/*
	 * NEEDSWORK: Eventually we want to be able to free gitdir and the rest
	 * of the environment before reinitializing it again, but we have some
	 * crazy code paths where we try to set gitdir with the current gitdir
	 * and we don't want to free gitdir before copying the passed in value.
	 */
	repo->gitdir = xstrdup(gitfile ? gitfile : path);

	repo_setup_env(repo);
}