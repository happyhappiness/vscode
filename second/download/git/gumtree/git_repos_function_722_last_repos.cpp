int git_config_get_maybe_bool(const char *key, int *dest)
{
	return repo_config_get_maybe_bool(the_repository, key, dest);
}