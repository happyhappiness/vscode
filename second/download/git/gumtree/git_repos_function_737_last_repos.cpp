int git_config_set_gently(const char *key, const char *value)
{
	return git_config_set_multivar_gently(key, value, NULL, 0);
}