int repo_config_get_value(struct repository *repo,
			  const char *key, const char **value)
{
	git_config_check_init(repo);
	return git_configset_get_value(repo->config, key, value);
}