int git_config_set_multivar_gently(const char *key, const char *value,
				   const char *value_regex, int multi_replace)
{
	return git_config_set_multivar_in_file_gently(NULL, key, value, value_regex,
						      multi_replace);
}