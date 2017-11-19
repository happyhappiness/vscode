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