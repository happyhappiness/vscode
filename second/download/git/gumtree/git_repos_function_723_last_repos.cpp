int git_config_get_pathname(const char *key, const char **dest)
{
	return repo_config_get_pathname(the_repository, key, dest);
}