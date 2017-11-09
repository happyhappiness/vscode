int repo_config_get_pathname(struct repository *repo,
			     const char *key, const char **dest)
{
	int ret;
	git_config_check_init(repo);
	ret = git_configset_get_pathname(repo->config, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}