int git_config_get_bool_or_int(const char *key, int *is_bool, int *dest)
{
	return repo_config_get_bool_or_int(the_repository, key, is_bool, dest);
}