int git_configset_get_value(struct config_set *cs, const char *key, const char **value)
{
	const struct string_list *values = NULL;
	/*
	 * Follows "last one wins" semantic, i.e., if there are multiple matches for the
	 * queried key in the files of the configset, the value returned will be the last
	 * value in the value list for that key.
	 */
	values = git_configset_get_value_multi(cs, key);

	if (!values)
		return 1;
	assert(values->nr > 0);
	*value = values->items[values->nr - 1].string;
	return 0;
}