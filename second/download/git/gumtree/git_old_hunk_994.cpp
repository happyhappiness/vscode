	ret = git_configset_get_pathname(&the_config_set, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}

int git_config_get_untracked_cache(void)
{
	int val = -1;
	const char *v;

	/* Hack for test programs like test-dump-untracked-cache */
