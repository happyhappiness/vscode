int repo_config_get_int(struct repository *repo,
			const char *key, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_int(repo->config, key, dest);
}