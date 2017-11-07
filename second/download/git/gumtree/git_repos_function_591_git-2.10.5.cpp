int git_config_get_string(const char *key, char **dest)
{
	git_config_check_init();
	return git_config_get_string_const(key, (const char **)dest);
}