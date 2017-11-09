int repo_config_get_string(struct repository *repo,
			   const char *key, char **dest)
{
	git_config_check_init(repo);
	return repo_config_get_string_const(repo, key, (const char **)dest);
}