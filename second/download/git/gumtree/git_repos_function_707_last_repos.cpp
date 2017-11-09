int repo_config_get_ulong(struct repository *repo,
			  const char *key, unsigned long *dest)
{
	git_config_check_init(repo);
	return git_configset_get_ulong(repo->config, key, dest);
}