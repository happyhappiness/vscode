int git_config_get_string(const char *key, char **dest)
{
	return repo_config_get_string(the_repository, key, dest);
}