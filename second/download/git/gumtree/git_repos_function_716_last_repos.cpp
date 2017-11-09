int git_config_get_string_const(const char *key, const char **dest)
{
	return repo_config_get_string_const(the_repository, key, dest);
}