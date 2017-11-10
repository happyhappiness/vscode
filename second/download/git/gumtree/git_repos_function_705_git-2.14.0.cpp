int repo_config_get_bool_or_int(struct repository *repo,
				const char *key, int *is_bool, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_bool_or_int(repo->config, key, is_bool, dest);
}