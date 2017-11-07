int git_config_get_untracked_cache(void)
{
	int val = -1;
	const char *v;

	/* Hack for test programs like test-dump-untracked-cache */
	if (ignore_untracked_cache_config)
		return -1;

	if (!git_config_get_maybe_bool("core.untrackedcache", &val))
		return val;

	if (!git_config_get_value("core.untrackedcache", &v)) {
		if (!strcasecmp(v, "keep"))
			return -1;

		error("unknown core.untrackedCache value '%s'; "
		      "using 'keep' default value", v);
		return -1;
	}

	return -1; /* default value */
}