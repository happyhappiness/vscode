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

NORETURN
void git_die_config_linenr(const char *key, const char *filename, int linenr)
{
	if (!filename)
		die(_("unable to parse '%s' from command-line config"), key);
	else
