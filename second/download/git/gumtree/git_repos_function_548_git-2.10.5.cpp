static int git_default_i18n_config(const char *var, const char *value)
{
	if (!strcmp(var, "i18n.commitencoding"))
		return git_config_string(&git_commit_encoding, var, value);

	if (!strcmp(var, "i18n.logoutputencoding"))
		return git_config_string(&git_log_output_encoding, var, value);

	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}