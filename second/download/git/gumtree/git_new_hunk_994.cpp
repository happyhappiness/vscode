	ret = git_configset_get_pathname(&the_config_set, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}

int git_config_get_expiry(const char *key, const char **output)
{
	int ret = git_config_get_string_const(key, output);
	if (ret)
		return ret;
	if (strcmp(*output, "now")) {
		unsigned long now = approxidate("now");
		if (approxidate(*output) >= now)
			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
	}
	return ret;
}

int git_config_get_untracked_cache(void)
{
	int val = -1;
	const char *v;

	/* Hack for test programs like test-dump-untracked-cache */
