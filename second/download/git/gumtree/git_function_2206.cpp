void git_config_set_multivar_in_file(const char *config_filename,
				     const char *key, const char *value,
				     const char *value_regex, int multi_replace)
{
	if (git_config_set_multivar_in_file_gently(config_filename, key, value,
						   value_regex, multi_replace) < 0)
		die(_("Could not set '%s' to '%s'"), key, value);
}