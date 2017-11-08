static int parse_submodule_params(struct diff_options *options, const char *value)
{
	if (!strcmp(value, "log"))
		DIFF_OPT_SET(options, SUBMODULE_LOG);
	else if (!strcmp(value, "short"))
		DIFF_OPT_CLR(options, SUBMODULE_LOG);
	else
		return -1;
	return 0;
}