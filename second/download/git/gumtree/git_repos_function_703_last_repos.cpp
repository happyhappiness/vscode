const struct string_list *repo_config_get_value_multi(struct repository *repo,
						      const char *key)
{
	git_config_check_init(repo);
	return git_configset_get_value_multi(repo->config, key);
}