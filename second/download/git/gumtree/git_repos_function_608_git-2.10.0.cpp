void git_config_set_in_file(const char *config_filename,
			    const char *key, const char *value)
{
	git_config_set_multivar_in_file(config_filename, key, value, NULL, 0);
}