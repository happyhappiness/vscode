int repo_config_get_maybe_bool(struct repository *repo,
			       const char *key, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_maybe_bool(repo->config, key, dest);
}