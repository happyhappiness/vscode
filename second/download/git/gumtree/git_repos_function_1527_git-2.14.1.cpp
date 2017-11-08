static int parse_submodule_params(struct diff_options *options, const char *value)
{
	if (!strcmp(value, "log"))
		options->submodule_format = DIFF_SUBMODULE_LOG;
	else if (!strcmp(value, "short"))
		options->submodule_format = DIFF_SUBMODULE_SHORT;
	else if (!strcmp(value, "diff"))
		options->submodule_format = DIFF_SUBMODULE_INLINE_DIFF;
	else
		return -1;
	return 0;
}