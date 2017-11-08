static int git_mailinfo_config(const char *var, const char *value, void *unused)
{
	if (!starts_with(var, "mailinfo."))
		return git_default_config(var, value, unused);
	if (!strcmp(var, "mailinfo.scissors")) {
		use_scissors = git_config_bool(var, value);
		return 0;
	}
	/* perhaps others here */
	return 0;
}