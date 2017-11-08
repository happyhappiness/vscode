static int git_default_archive_config(const char *var, const char *value,
				      void *cb)
{
	if (!strcmp(var, "uploadarchive.allowunreachable"))
		remote_allow_unreachable = git_config_bool(var, value);
	return git_default_config(var, value, cb);
}