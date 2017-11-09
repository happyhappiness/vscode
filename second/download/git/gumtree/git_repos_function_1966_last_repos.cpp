int git_config_colorbool(const char *var, const char *value)
{
	if (value) {
		if (!strcasecmp(value, "never"))
			return 0;
		if (!strcasecmp(value, "always"))
			return 1;
		if (!strcasecmp(value, "auto"))
			return GIT_COLOR_AUTO;
	}

	if (!var)
		return -1;

	/* Missing or explicit false to turn off colorization */
	if (!git_config_bool(var, value))
		return 0;

	/* any normal truth value defaults to 'auto' */
	return GIT_COLOR_AUTO;
}