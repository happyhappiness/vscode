static int git_tar_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "tar.umask")) {
		if (value && !strcmp(value, "user")) {
			tar_umask = umask(0);
			umask(tar_umask);
		} else {
			tar_umask = git_config_int(var, value);
		}
		return 0;
	}

	return tar_filter_config(var, value, cb);
}