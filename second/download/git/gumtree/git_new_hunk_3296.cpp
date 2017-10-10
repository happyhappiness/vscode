}

void git_config_set_multivar_in_file(const char *config_filename,
				     const char *key, const char *value,
				     const char *value_regex, int multi_replace)
{
	if (!git_config_set_multivar_in_file_gently(config_filename, key, value,
						    value_regex, multi_replace))
		return;
	if (value)
		die(_("could not set '%s' to '%s'"), key, value);
	else
		die(_("could not unset '%s'"), key);
}

int git_config_set_multivar_gently(const char *key, const char *value,
				   const char *value_regex, int multi_replace)
{
	return git_config_set_multivar_in_file_gently(NULL, key, value, value_regex,
