static int git_mailinfo_config(const char *var, const char *value, void *mi_)
{
	struct mailinfo *mi = mi_;

	if (!starts_with(var, "mailinfo."))
		return git_default_config(var, value, NULL);
	if (!strcmp(var, "mailinfo.scissors")) {
		mi->use_scissors = git_config_bool(var, value);
		return 0;
	}
	/* perhaps others here */
	return 0;
}