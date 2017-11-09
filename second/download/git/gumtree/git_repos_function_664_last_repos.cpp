static int git_default_mailmap_config(const char *var, const char *value)
{
	if (!strcmp(var, "mailmap.file"))
		return git_config_pathname(&git_mailmap_file, var, value);
	if (!strcmp(var, "mailmap.blob"))
		return git_config_string(&git_mailmap_blob, var, value);

	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}