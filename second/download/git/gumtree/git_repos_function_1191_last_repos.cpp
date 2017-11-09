void repo_clear(struct repository *repo)
{
	free(repo->gitdir);
	repo->gitdir = NULL;
	free(repo->commondir);
	repo->commondir = NULL;
	free(repo->objectdir);
	repo->objectdir = NULL;
	free(repo->graft_file);
	repo->graft_file = NULL;
	free(repo->index_file);
	repo->index_file = NULL;
	free(repo->worktree);
	repo->worktree = NULL;
	free(repo->submodule_prefix);
	repo->submodule_prefix = NULL;

	if (repo->config) {
		git_configset_clear(repo->config);
		free(repo->config);
		repo->config = NULL;
	}

	if (repo->submodule_cache) {
		submodule_cache_free(repo->submodule_cache);
		repo->submodule_cache = NULL;
	}

	if (repo->index) {
		discard_index(repo->index);
		free(repo->index);
		repo->index = NULL;
	}
}