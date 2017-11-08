static int write_one_config(const char *key, const char *value, void *data)
{
	return git_config_set_multivar_gently(key,
					      value ? value : "true",
					      CONFIG_REGEX_NONE, 0);
}