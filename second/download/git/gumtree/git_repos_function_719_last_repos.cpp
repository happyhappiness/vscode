int git_config_get_ulong(const char *key, unsigned long *dest)
{
	return repo_config_get_ulong(the_repository, key, dest);
}