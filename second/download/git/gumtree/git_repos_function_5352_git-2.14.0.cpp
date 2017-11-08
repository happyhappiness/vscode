static int get_common_prefix_len(const char *common_prefix)
{
	int common_prefix_len;

	if (!common_prefix)
		return 0;

	common_prefix_len = strlen(common_prefix);

	/*
	 * If the prefix has a trailing slash, strip it so that submodules wont
	 * be pruned from the index.
	 */
	if (common_prefix[common_prefix_len - 1] == '/')
		common_prefix_len--;

	return common_prefix_len;
}