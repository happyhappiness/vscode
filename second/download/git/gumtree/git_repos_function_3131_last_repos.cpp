int git_default_advice_config(const char *var, const char *value)
{
	const char *k;
	int i;

	if (!skip_prefix(var, "advice.", &k))
		return 0;

	for (i = 0; i < ARRAY_SIZE(advice_config); i++) {
		if (strcmp(k, advice_config[i].name))
			continue;
		*advice_config[i].preference = git_config_bool(var, value);
		return 0;
	}

	return 0;
}