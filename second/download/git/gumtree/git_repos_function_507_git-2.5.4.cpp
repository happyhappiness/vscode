int git_config_set(const char *key, const char *value)
{
	return git_config_set_multivar(key, value, NULL, 0);
}