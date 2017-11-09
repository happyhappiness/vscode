static void git_config_check_init(struct repository *repo)
{
	if (repo->config && repo->config->hash_initialized)
		return;
	repo_read_config(repo);
}