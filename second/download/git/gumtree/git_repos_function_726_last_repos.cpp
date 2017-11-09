int git_config_get_split_index(void)
{
	int val;

	if (!git_config_get_maybe_bool("core.splitindex", &val))
		return val;

	return -1; /* default value */
}