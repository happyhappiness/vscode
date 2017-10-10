		return val;

	if (!git_config_get_value("core.untrackedcache", &v)) {
		if (!strcasecmp(v, "keep"))
			return -1;

		error(_("unknown core.untrackedCache value '%s'; "
			"using 'keep' default value"), v);
		return -1;
	}

	return -1; /* default value */
}

int git_config_get_split_index(void)
{
	int val;

	if (!git_config_get_maybe_bool("core.splitindex", &val))
		return val;

	return -1; /* default value */
}

int git_config_get_max_percent_split_change(void)
{
	int val = -1;

	if (!git_config_get_int("splitindex.maxpercentchange", &val)) {
		if (0 <= val && val <= 100)
			return val;

		return error(_("splitIndex.maxPercentChange value '%d' "
			       "should be between 0 and 100"), val);
	}

	return -1; /* default value */
}

NORETURN
void git_die_config_linenr(const char *key, const char *filename, int linenr)
{
	if (!filename)
		die(_("unable to parse '%s' from command-line config"), key);
	else
