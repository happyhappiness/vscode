int git_config_set_in_file_gently(const char *config_filename,
				  const char *key, const char *value)
{
	return git_config_set_multivar_in_file_gently(config_filename, key, value, NULL, 0);
}