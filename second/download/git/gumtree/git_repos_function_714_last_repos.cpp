int git_config_get_value(const char *key, const char **value)
{
	return repo_config_get_value(the_repository, key, value);
}