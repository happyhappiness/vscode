int git_config_get_int(const char *key, int *dest)
{
	return repo_config_get_int(the_repository, key, dest);
}