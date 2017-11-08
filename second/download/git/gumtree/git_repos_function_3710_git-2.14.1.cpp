void repo_read_gitmodules(struct repository *repo)
{
	char *gitmodules_path = repo_worktree_path(repo, ".gitmodules");

	git_config_from_file(gitmodules_cb, gitmodules_path, repo);
	free(gitmodules_path);
}