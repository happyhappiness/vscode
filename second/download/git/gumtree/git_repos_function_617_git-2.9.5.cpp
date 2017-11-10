void git_config_set_multivar(const char *key, const char *value,
			     const char *value_regex, int multi_replace)
{
	git_config_set_multivar_in_file(NULL, key, value, value_regex,
					multi_replace);
}