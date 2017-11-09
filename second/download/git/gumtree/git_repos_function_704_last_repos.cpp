int repo_config_get_string_const(struct repository *repo,
				 const char *key, const char **dest)
{
	int ret;
	git_config_check_init(repo);
	ret = git_configset_get_string_const(repo->config, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}