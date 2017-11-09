static void repo_config_clear(struct repository *repo)
{
	if (!repo->config || !repo->config->hash_initialized)
		return;
	git_configset_clear(repo->config);
}